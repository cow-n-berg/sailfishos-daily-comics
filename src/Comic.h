/**
 * Copyright (c) 2015 Damien Tardy-Panis
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 **/

#ifndef COMIC_H
#define COMIC_H

#include <QObject>

#include <QUrl>
#include <QLocale>

class QNetworkAccessManager;
class QNetworkReply;

class Comic : public QObject
{
    Q_OBJECT

public:
    explicit Comic(QObject *parent = 0);
    ~Comic();

    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString author() const = 0;
    virtual QUrl homepage() const = 0;
    virtual QLocale::Country country() const = 0;
    virtual QLocale::Language language() const = 0;
    virtual QDate startDate() const = 0;
    virtual QDate endDate() const = 0;
    virtual QUrl extractStripUrl(QByteArray data) = 0;

    QUrl currentStripUrl() const { return m_currentStripUrl; }
    bool favorite() const { return m_favorite; }

    void setFavorite(const bool favorite) { m_favorite = favorite; }

    void fetchCurrentStripUrl();

protected:
    virtual QUrl stripSourceUrl() const = 0;

    void setCurrentStripUrl(const QUrl currentStripUrl) { m_currentStripUrl = currentStripUrl; }

private slots:
    void parse();

signals:
    void currentStripUrlFetched();

protected:
    QUrl m_currentStripUrl;
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_currentReply;
    bool m_favorite;
};

#endif // COMIC_H
