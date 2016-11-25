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

#ifndef RISIPACCOUNTPROFILE_H
#define RISIPACCOUNTPROFILE_H

#include <QObject>
#include "risipglobals.h"

class RisipAccountProfile : public QObject
{
    Q_OBJECT

public:
    enum Status {
        Ready = 1,
        Registering,
        Updating,
        Empty,
        NotCreated,
        Error = -1
    };

    enum DeviceType {
        SIP = 11,
        IAX2,
        Virtual
    };

    Q_ENUM(Status)
    Q_ENUM(DeviceType)
    Q_PROPERTY(int userId READ userId NOTIFY userIdChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString creditBalance READ creditBalance NOTIFY creditBalanceChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString postCode READ postCode WRITE setPostCode NOTIFY postCodeChanged)
    Q_PROPERTY(QString vatNumber READ vatNumber WRITE setVatNumber NOTIFY vatNumberChanged)
    Q_PROPERTY(int currency READ currency WRITE setCurrency NOTIFY currencyChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString mobileNumber READ mobileNumber WRITE setMobileNumber NOTIFY mobileNumberChanged)
    Q_PROPERTY(int deviceType READ deviceType WRITE setDeviceType NOTIFY deviceTypeChanged)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)

    explicit RisipAccountProfile(QObject *parent = 0);
    ~RisipAccountProfile();

    int userId() const;
    bool valid() const;

    QString username() const;
    void setUsername(const QString & username);

    QString password() const;
    void setPassword(const QString &password);

    QString creditBalance() const;

    QString email() const;
    void setEmail(const QString &email);

    QString firstName() const;
    void setFirstName(const QString &firstname);

    QString lastName() const;
    void setLastName(const QString &lastname);

    QString country() const;
    void setCountry(const QString &country);

    QString city() const;
    void setCity(const QString &city);

    QString address() const;
    void setAddress(const QString &address);

    QString postCode() const;
    void setPostCode(const QString &code);

    QString vatNumber() const;
    void setVatNumber(const QString &number);

    int currency() const;
    void setCurrency(int currency);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &phone);

    QString mobileNumber() const;
    void setMobileNumber(const QString &mobile);

    int deviceType() const;
    void setDeviceType(int type);

    int status() const;
    void setStatus(int status);

    Q_INVOKABLE void reset();

Q_SIGNALS:
    void userIdChanged(int id);
    void usernameChanged(const QString &username);
    void passwordChanged(const QString &password);
    void creditBalanceChanged(const QString &balance);
    void emailChanged(const QString &email);
    void firstNameChanged(const QString &firstname);
    void lastNameChanged(const QString &lastname);
    void countryChanged(const QString &country);
    void cityChanged(const QString &city);
    void addressChanged(const QString &address);
    void postCodeChanged(const QString &postcode);
    void vatNumberChanged(const QString &vat);
    void currencyChanged(int currency);
    void phoneNumberChanged(const QString &phonenumber);
    void mobileNumberChanged(const QString &mobile);
    void validChanged(bool valid);
    void deviceTypeChanged(int type);
    void statusChanged(int status);

private:
    class Private;
    Private *m_data;
};

#endif // RISIPACCOUNTPROFILE_H
