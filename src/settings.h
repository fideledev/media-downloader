/*
 *
 *  Copyright (c) 2021
 *  name : Francis Banyikwa
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QComboBox>
#include <QPixmap>

#include <vector>
#include <memory>

#include <QStandardPaths>

class Logger ;
class QApplication ;

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class settings
{
public:
	class darkModes
	{
	public:
		darkModes() = default;
		darkModes( const QString& m ) : m_theme( m )
		{
		}
		QStringList typesUntranslated() const
		{
			QStringList m ;

			for( const auto& it : m_strings ){

				m.append( it.untranslated ) ;
			}

			return m ;
		}
		QStringList typesTranslated() const
		{
			QStringList m ;

			for( const auto& it : m_strings ){

				m.append( it.translated ) ;
			}

			return m ;
		}
		const QString& translatedAt( int s ) const
		{
			return m_strings[ static_cast< size_t >( s ) ].translated ;
		}
		const QString& unTranslatedAt( int s ) const
		{
			return m_strings[ static_cast< size_t >( s ) ].untranslated ;
		}
		int translatedIndexAt( const QString& e ) const
		{
			for( size_t i = 0 ; i < m_strings.size() ; i++ ){

				if( m_strings[ i ].translated == e ){

					return static_cast< int >( i ) ;
				}
			}

			return 0 ;
		}
		int unTranslatedIndexAt( const QString& e ) const
		{
			for( size_t i = 0 ; i < m_strings.size() ; i++ ){

				if( m_strings[ i ].untranslated == e ){

					return static_cast< int >( i ) ;
				}
			}

			return 0 ;
		}
		bool fusionTheme() const
		{
			return m_theme == "Dark Theme 1" ;
		}
		bool darkModeIsSet() const
		{
			return this->unTranslatedAt( 0 ) != m_theme ;
		}
		QString themeFileName() const
		{
			if( m_theme == "Dark Theme 2" ){

				return ":dark.qss" ;

			}else if( m_theme == "Dark Theme 3" ){

				return ":qdarkstyle/dark/style.qss" ;
			}else{
				return QString() ;
			}
		}
		void setComboBox( QComboBox& cb,const QString& dm ) const
		{
			cb.clear() ;

			cb.addItems( this->typesTranslated() ) ;

			cb.setCurrentIndex( this->unTranslatedIndexAt( dm ) ) ;
		}
	private:
		int indexAt( const QString& e,const QStringList& s ) const
		{
			for( int i = 0 ; i < s.size() ; i++ ){

				if( s[ i ] == e ){

					return i ;
				}
			}

			return 0 ;
		}

		QString m_theme ;

		struct Pair{
			QString untranslated ;
			QString translated ;
		};

		std::vector<Pair> m_strings{ { "Normal",QObject::tr( "Normal" ) },
					     { "Dark Theme 1",QObject::tr( "Dark Theme 1" ) },
					     { "Dark Theme 2",QObject::tr( "Dark Theme 2" ) },
					     { "Dark Theme 3",QObject::tr( "Dark Theme 3" ) },
					   } ;
	} ;

	enum class tabName{ basic,batch,playlist } ;

	settings() ;

	QSettings& bk() ;

	int tabNumber() ;
	size_t maxConcurrentDownloads() ;

	QString downloadFolder() ;
	QString libraryDownloadFolder() ;
	QString downloadFolder( Logger& ) ;
	QString localizationLanguagePath() ;
	QString localizationLanguage() ;
	QString commandOnSuccessfulDownload() ;
	QString commandWhenAllFinished() ;
	QString darkMode() ;
	QString defaultEngine( settings::tabName,const QString& ) ;
	QString cookieFilePath( const QString& engineName ) ;
	QString windowsDimensions( const QString& windowName ) ;
	QString engineDefaultDownloadOptions( const QString& engineName ) ;
	QString playlistRangeHistoryLastUsed() ;
	QString configPaths() ;

	QStringList getOptionsHistory( settings::tabName ) ;
	QStringList playlistRangeHistory() ;
	QStringList playlistUrlHistory() ;

	QString lastUsedOption( const QString&,settings::tabName ) ;

	QStringList localizationLanguages() ;

	QByteArray highDpiScalingFactor() ;

	QPixmap defaultVideoThumbnailIcon( settings::tabName ) ;

	static bool portableVersion() ;
	static QString portableVersionConfigPath() ;

	bool enabledHighDpiScaling() ;
	bool showTrayIcon() ;
	bool autoDownload() ;
	bool showVersionInfoWhenStarting() ;
	bool concurrentDownloading() ;
	bool useSystemProvidedVersionIfAvailable() ;
	bool showThumbnails() ;
	bool saveHistory() ;
	bool playlistDownloaderSaveHistory() ;
	bool singleInstance() ;

	int stringTruncationSize() ;
	int historySize() ;

	int thumbnailWidth( settings::tabName ) ;
	int thumbnailHeight( settings::tabName ) ;

	void clearOptionsHistory( settings::tabName ) ;
	void setEngineDefaultDownloadOptions( const QString& engineName,const QString& options ) ;
	void addToplaylistRangeHistory( const QString& ) ;
	void clearPlaylistRangeHistory() ;
	void clearPlaylistUrlHistory() ;
	void addOptionsHistory( const QString&,settings::tabName ) ;
	void setTheme( QApplication& ) ;
	void setUseSystemProvidedVersionIfAvailable( bool ) ;
	void setMaxConcurrentDownloads( int ) ;
	void setTabNumber( int ) ;
	void setShowThumbnails( bool ) ;
	void setPlaylistDownloaderSaveHistory( bool ) ;
	void setShowVersionInfoWhenStarting( bool ) ;
	void setDarkMode( const QString& ) ;
	void setPlaylistRangeHistoryLastUsed( const QString& ) ;
	void setHighDpiScalingFactor( const QString& ) ;
	void setlibraryDownloadFolder( const QString& ) ;
	void setCookieFilePath( const QString& engineName,const QString& cookieFilePath ) ;
	void setDefaultEngine( const QString&,settings::tabName ) ;
	void setLastUsedOption( const QString& engineName,const QString& options,settings::tabName ) ;
	void setDownloadFolder( const QString& ) ;
	void setLocalizationLanguage( const QString& language ) ;
	void setWindowDimensions( const QString& window,const QString& dimenstion ) ;
private:
	bool m_EnableHighDpiScaling ;
	std::unique_ptr< QSettings > m_settingsP ;
	QSettings& m_settings ;
	bool m_portableVersion ;
};

#endif
