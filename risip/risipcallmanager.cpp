/***********************************************************************************
**    Copyright (C) 2016  Petref Saraci
**    http://risip.io
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**    This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You have received a copy of the GNU General Public License
**    along with this program. See LICENSE.GPLv3
**    A copy of the license can be found also here <http://www.gnu.org/licenses/>.
**
************************************************************************************/
#include "risipcallmanager.h"

#include "globals.h"
#include "risip.h"
#include "risipcall.h"
#include "risipaccount.h"
#include "risipbuddy.h"
#include "risipaccountconfiguration.h"
#include "risipcontactmanager.h"
#include "risipmodels.h"

#include <QSortFilterProxyModel>
#include <QDebug>

RisipCallManager *RisipCallManager::m_callManagerInstance = NULL;
RisipCallManager *RisipCallManager::instance()
{
    if(m_callManagerInstance == NULL)
        m_callManagerInstance = new RisipCallManager;

    return m_callManagerInstance;
}

/**
 * @brief RisipCallManager::RisipCallManager
 * @param parent
 *
 * RisipCallManager is a signleton type and it provides functionality for managing Calls and Call History.
 */
RisipCallManager::RisipCallManager(QObject *parent)
    :QObject(parent)
    ,m_activeAccount(Risip::instance()->defaultAccount())
    ,m_activeCall(NULL)
    ,m_activeCallHistoryModel(NULL)
    ,m_callHistoryModels()
{
    connect(m_activeAccount, &RisipAccount::incomingCall,
            this, &RisipCallManager::accountIncomingCall);
}

/**
 * @brief RisipCallManager::setActiveCall
 * @param call
 *
 * Internal API . No need to use this anywhere.
 */
void RisipCallManager::setActiveCall(RisipCall *call)
{
    if(m_activeCall != call) {
        m_activeCall = call;
        emit activeCallChanged(m_activeCall);
    }
}

QAbstractItemModel *RisipCallManager::activeCallHistoryModel() const
{
    return qobject_cast<RisipCallHistoryModel *>(m_activeCallHistoryModel);
}

void RisipCallManager::setActiveCallHistoryModel(QAbstractItemModel *model)
{
    if(m_activeCallHistoryModel != model) {
        m_activeCallHistoryModel = model;
        emit activeCallHistoryModelChanged(m_activeCallHistoryModel);
    }
}

QQmlListProperty<QAbstractItemModel> RisipCallManager::callHistoryModels()
{
    QList<QAbstractItemModel *> models = m_callHistoryModels.values();
    return QQmlListProperty<QAbstractItemModel>(this, models);
}

QAbstractItemModel *RisipCallManager::callHistoryModelForAccount(const QString &account) const
{
    if(m_callHistoryModels.contains(account))
        return qobject_cast<RisipCallHistoryModel *>(m_callHistoryModels[account]);

    return NULL;
}

RisipCallManager::~RisipCallManager()
{
    m_callManagerInstance = NULL;
}

RisipAccount *RisipCallManager::activeAccount() const
{
    return m_activeAccount;
}

/**
 * @brief RisipCallManager::setDefaultAccount
 * @param account as the new default account
 *
 * Setting the account as the default SIP account for this call manager, hence this account will be used
 * for all incoming/outgoing calls and other call operations.
 */
void RisipCallManager::setActiveAccount(RisipAccount *account)
{
    if(!account)
        return;

    if(m_activeAccount !=account) {

        disconnect(m_activeAccount, &RisipAccount::incomingCall,
                this, &RisipCallManager::accountIncomingCall);

        m_activeAccount = account;
        if(!m_activeAccount)
            m_activeAccount = Risip::instance()->defaultAccount();

        connect(m_activeAccount, &RisipAccount::incomingCall,
                this, &RisipCallManager::accountIncomingCall, Qt::UniqueConnection);

        if(callHistoryModelForAccount(m_activeAccount->configuration()->uri()))
            setActiveCallHistoryModel(callHistoryModelForAccount(m_activeAccount->configuration()->uri()));
        //TODO what if call history model does not exists?

        emit activeAccountChanged(m_activeAccount);
    }
}

RisipCall *RisipCallManager::activeCall()
{
    return m_activeCall;
}

void RisipCallManager::callContact(const QString contact)
{
    RisipBuddy *buddy = m_activeAccount->findBuddy(
                RisipGlobals::formatToSip(contact, m_activeAccount->configuration()->uri()));
    if(buddy == NULL) {
        buddy = new RisipBuddy;
        buddy->setAccount(activeAccount());
        buddy->setContact(contact);
    }

    callBuddy(buddy);
}

void RisipCallManager::callBuddy(RisipBuddy *buddy)
{
    RisipCall *call = new RisipCall(this);
    call->setBuddy(buddy);
    call->setAccount(m_activeAccount);
    call->call();
    emit outgoingCall(call);

    //adding call record for the active account.
    qobject_cast<RisipCallHistoryModel *>(m_activeCallHistoryModel)->addCallRecord(call);
    setActiveCall(call);
}

void RisipCallManager::callPhone(const QString &number)
{
    Q_UNUSED(number)
    qDebug()<<"calling phones is not implemented";
}

/**
 * @brief RisipCallManager::createModelsForAccount
 * @param activeAccount
 *
 * Internal API.
 *
 * Used by Risip when creating accounts. @see Risip::createAccount
 */
void RisipCallManager::createModelsForAccount(RisipAccount *account)
{
    if(!account)
        return;

    if(!m_callHistoryModels.contains(account->configuration()->uri())) {
        RisipCallHistoryModel *model = new RisipCallHistoryModel(this);
        m_callHistoryModels[account->configuration()->uri()] = model;
        model->setAccount(account);
    }
}

/**
 * @brief RisipCallManager::removeModelsForAccount
 * @param activeAccount
 *
 * Internal API.
 *
 * Used by Risip when account is removed. @see Risip::removeAccount
 */
void RisipCallManager::removeModelsForAccount(const RisipAccount *account)
{
    if(!account)
        return;

    if(m_callHistoryModels.contains(account->configuration()->uri()))
        delete m_callHistoryModels[account->configuration()->uri()];
}

/**
 * @brief RisipCallManager::accountIncomingCall
 *
 * Internal API.
 * This private slot is called each time an incoming call is received from the default account.
 */
void RisipCallManager::accountIncomingCall()
{
    RisipCall *call = new RisipCall(this);
    call->setAccount(m_activeAccount);
    call->initiateIncomingCall();

    QString remoteUri = QString::fromStdString(call->pjsipCall()->getInfo().remoteUri);
    RisipBuddy *buddy = m_activeAccount->findBuddy(remoteUri);
    if(buddy == NULL) {
        buddy = new RisipBuddy;
        buddy->setUri(remoteUri);
        buddy->setAccount(activeAccount());
    }

    call->setBuddy(buddy);
    emit incomingCall(call);

    qobject_cast<RisipCallHistoryModel *>(m_activeCallHistoryModel)->addCallRecord(call);
    //setting the call as the active one
    setActiveCall(call);
}
