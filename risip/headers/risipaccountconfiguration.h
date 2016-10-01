/***********************************************************************************
**    Copyright (C) 2016  Petref Saraci
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
**    A copy of the license is also here <http://www.gnu.org/licenses/>.
**
************************************************************************************/

#ifndef RISIPACCOUNTCONFIGURATION_H
#define RISIPACCOUNTCONFIGURATION_H

#include "risipaccount.h"

class RisipAccountConfiguration : public QObject
{
    Q_OBJECT
public:

    enum Codecs {
        iLBC = 1,
        G711,
        G722,
        Speex20,
        Speex30,
        Opus
    };

    enum NetworkProtocol {
        UDP = 1,
        TCP,
        UDP6,
        TCP6,
        SCTP,
        TLS,
        TLS6,
        LOOP
    };

    Q_ENUM(Codecs)
    Q_ENUM(NetworkProtocol)

    //pjsip-defined
    Q_PROPERTY(RisipAccount * account READ account WRITE setAccount NOTIFY accountChanged)
    Q_PROPERTY(QString uri READ uri WRITE setUri NOTIFY uriChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString scheme READ scheme WRITE setScheme NOTIFY schemeChanged)
    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(QString proxyServer READ proxyServer WRITE setProxyServer NOTIFY proxyServerChanged)
    Q_PROPERTY(int proxyPort READ proxyPort WRITE setProxyPort NOTIFY proxyPortChanged)
    Q_PROPERTY(int transportId READ transportId WRITE setTransportId NOTIFY transportIdChanged)

    //user-defined
    Q_PROPERTY(int networkProtocol READ networkProtocol WRITE setNetworkProtocol NOTIFY networkProtocolChanged)
    Q_PROPERTY(int localPort READ localPort WRITE setLocalPort NOTIFY localPortChanged)
    Q_PROPERTY(bool randomLocalPort READ randomLocalPort WRITE setRandomLocalPort NOTIFY randomLocalPortChanged)

    RisipAccountConfiguration(QObject *parent = 0);
    ~RisipAccountConfiguration();

    RisipAccount *account() const;
    void setAccount(RisipAccount *account);

    QString uri() const;
    void setUri(QString accountUri);

    QString userName() const;
    void setUserName(QString &name);

    QString password() const;
    void setPassword(QString &pass);

    QString scheme() const;
    void setScheme(QString &credScheme);

    QString serverAddress() const;
    void setServerAddress(QString &address);

    QString proxyServer() const;
    void setProxyServer(QString &proxy);

    int proxyPort() const;
    void setProxyPort(int port);

    int transportId() const;
    void setTransportId(int transId);

    int networkProtocol() const;
    void setNetworkProtocol(int protocol);

    int localPort() const;
    void setLocalPort(int port);

    bool randomLocalPort() const;
    void setRandomLocalPort(bool random);

    void setCodecPriority(Codecs codecId, int priority);

    AccountConfig pjsipAccountConfig();
    TransportConfig pjsipTransportConfig();

Q_SIGNALS:
    void accountChanged(RisipAccount *account);
    void uriChanged(QString &uri);
    void userNameChanged(QString &username);
    void passwordChanged(QString &password);
    void schemeChanged(QString &scheme);
    void serverAddressChanged(QString &serverAddress);
    void proxyServerChanged(QString &proxy);
    void proxyPortChanged(int &port);
    void transportIdChanged(int transportId);
    void networkProtocolChanged(int protocol);
    void localPortChanged(int port);
    void randomLocalPortChanged(bool randomPort);

private:
    RisipAccount *m_risipAccount;
    AccountConfig m_accountConfig;
    AuthCredInfo m_accountCredentials;
    TransportConfig m_transportConfiguration;

    int m_networkProtocol;
    QString m_proxyAddress;
    int m_proxyPort;
    bool m_randomLocalPort;
};

#endif // RISIPACCOUNTCONFIGURATION_H