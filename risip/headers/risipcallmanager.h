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
#ifndef RISIPCALLMANAGER_H
#define RISIPCALLMANAGER_H

#include <QObject>
#include <QAbstractItemModel>
#include <QQmlListProperty>

class RisipAccount;
class RisipBuddy;
class RisipCall;
class RisipCallHistoryModel;

class RisipCallManager : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(RisipAccount * activeAccount READ activeAccount WRITE setActiveAccount NOTIFY activeAccountChanged)
    Q_PROPERTY(RisipCall * activeCall READ activeCall NOTIFY activeCallChanged)
    Q_PROPERTY(QAbstractItemModel * activeCallHistoryModel READ activeCallHistoryModel WRITE setActiveCallHistoryModel NOTIFY activeCallHistoryModelChanged)
    Q_PROPERTY(QQmlListProperty<QAbstractItemModel> callHistoryModels READ callHistoryModels NOTIFY callHistoryModelsChanged)

    static RisipCallManager *instance();
    ~RisipCallManager();

    RisipAccount *activeAccount() const;
    void setActiveAccount(RisipAccount *activeAccount);

    RisipCall *activeCall();
    void setActiveCall(RisipCall *call);

    QAbstractItemModel *activeCallHistoryModel() const;
    void setActiveCallHistoryModel(QAbstractItemModel *model);

    QQmlListProperty<QAbstractItemModel> callHistoryModels();

    Q_INVOKABLE QAbstractItemModel *callHistoryModelForAccount(const QString &account) const;
    Q_INVOKABLE void callContact(const QString uri);
    Q_INVOKABLE void callBuddy(RisipBuddy *buddy);
    Q_INVOKABLE void callPhone(const QString &number);

    void createModelsForAccount(RisipAccount *account);
    void removeModelsForAccount(const RisipAccount *account);

Q_SIGNALS:
    void activeAccountChanged(RisipAccount *activeAccount);
    void activeCallChanged(RisipCall *call);
    void activeCallHistoryModelChanged(QAbstractItemModel *model);
    void callHistoryModelsChanged(QQmlListProperty<QAbstractItemModel> models);
    void defaultAccountAlwaysChanged(bool always);
    void incomingCall(RisipCall *call);
    void outgoingCall(RisipCall *call);

private Q_SLOTS:
    void accountIncomingCall();

private:
    explicit RisipCallManager(QObject *parent = 0);
    static RisipCallManager *m_callManagerInstance;

    RisipAccount *m_activeAccount;
    RisipCall *m_activeCall;
    QAbstractItemModel *m_activeCallHistoryModel;
    QHash<QString, QAbstractItemModel *> m_callHistoryModels;
};

#endif // RISIPCALLMANAGER_H
