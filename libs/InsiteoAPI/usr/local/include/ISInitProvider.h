//
//  ISInitProvider.h
//  CommonAPI
//
//  Created by INSITEO on 17/12/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISInitProvider.h
 ISInitProvider
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

extern int const DEFAULT_APPLICATION_VERSION;

#import "ISPCancelable.h"
#import "ISRODBHelper.h"
#import "ISZone.h"
#import "ISMap.h"
#import "ISTypes.h"
#import "ISInsiteoError.h"
#import "ISPackage.h"

/*!
 API initialization handler.
 @param error Corresponding initialization error (nil if success).
 @param newPackages All new available packages (nil if fail).
 @return An array of all packages you want to update.
 */
typedef NSArray * (^ISInitProviderStartHandler)(ISInsiteoError * error, NSArray * newPackages);

/*!
 API update handler.
 @param error Corresponding update error (nil if success).
 */
typedef void (^ISInitProviderUpdateHandler)(ISInsiteoError * error);

/*!
 API update progress handler.
 @param packageType Current treated package type.
 @param download Boolean used to know if the package is currently downloading or installing.
 @param progress Current package task progress (size for download, files count for install).
 @param total Total size of files count.
 */
typedef void (^ISInitProviderUpdateProgressHandler)(ISPackageType packageType, Boolean download, int progress, int total);

@class PackageUpdater;
@class InitInformation;
@class InitParameters;

@protocol PDebugListener;

/*! 
 Class used to represent an API initialization task. 
 */
@interface ISInitTask : NSObject <ISPCancelable>

/*!
 Main constructor.
 @param initParameters The initialization parameters to use.
 */
- (id)initWithInitParameters:(InitParameters *)initParameters;

/*!
 Method called to initialize the API.
 */
- (void)initAPI;

@end

/*!
 Class used to provide all generic INSITEO methods.
 */
@interface ISInitProvider : NSObject

/*!
 Boolean used to know if the online initialization succeeded.
 */
@property (readwrite) Boolean isInitialized;

/*!
 Init start handler.
 */
@property (nonatomic, copy) ISInitProviderStartHandler startHandler;

/*!
 Init update handler.
 */
@property (nonatomic, copy) ISInitProviderUpdateHandler updateHandler;

/*!
 Init update progress handler.
 */
@property (nonatomic, copy) ISInitProviderUpdateProgressHandler updateProgressHandler;

/*!
 The current root map.
 */
@property (nonatomic, retain) ISMap * mapRoot;

/*!
 All the maps stored in an NSDictionnary (key <=> map identifier : NSNumber).
 */
@property (nonatomic, retain) NSDictionary * maps;

/*!
 An array containing all sorted maps.
 */
@property (nonatomic, readonly) NSArray * sortedMaps;

/*!
 All maps zones.
 */
@property (nonatomic, retain) NSDictionary * zones;

/*!
 Last initialization date.
 */
@property (nonatomic, retain) NSDate * lastInitDate;

/*!
 Application site identifier.
 */
@property (nonatomic, readwrite) int siteId;

/*!
 Application server URL.
 */
@property (nonatomic, retain) NSString * serverUrl;

/*!
 Application language.
 */
@property (nonatomic, retain) NSString * language;

/*!
 INSITEO server type.
 */
@property (nonatomic, readwrite) ISEServerType serverType;

/*!
 Application version.
 */
@property (nonatomic, readwrite) int applicationVersion;

/*!
 INSITEO packages updater.
 */
@property (nonatomic, retain) PackageUpdater * packageUpdater;

/*!
 Boolean used to know if we can start analytics automatically.
 */
@property (nonatomic, readonly) Boolean analyticsAutoStart;

/*!
 Current map render mode (2D or 3D).
 */
@property (nonatomic, readwrite) ISERenderMode renderMode;

/*!
 Initialization URL.
 */
@property (nonatomic, retain) NSString * startPath;

/*!
 Application resources read-only data path.
 */
@property (nonatomic, retain) NSString * dataPath;

/*!
 Application resources read-write data path.
 */
@property (nonatomic, retain) NSString * rwDataPath;

/*!
 Init provider data.
 */
@property (nonatomic, retain) InitInformation * apiInformation;

/*!
 A NSArray which contains all application database helpers.
 */
@property (nonatomic, retain) NSMutableDictionary * dbHelpers;

/*!
 A debug listener reference (used to get debug event).
 */
@property (assign) id<PDebugListener> debugListener;

/*!
 Static method used to get the unique instance of the InitProvider.
 @return InitProvider unique instance.
 */
+ (ISInitProvider *)instance;

/*!
 Static method used to set the API key.
 @param apiKey The API key to use.
 */
+ (void)setAPIKey:(NSString *)apiKey;

/*!
 Static method used to get the API key used.
 @result The API key used.
 */
+ (NSString *)APIKey;

/*!
 Static method used to set the API token.
 @param isToken The API token to use.
 */
+ (void)setISToken:(NSString *)isToken;

/*!
 Static method used to get the API token used.
 @result The API token used.
 */
+ (NSString *)ISToken;

/*!
 Static method used to get the server NSString for use in URLs.
 @param serverType INSITEO server type.
 @return The related NSString to use in URLs only.
 */
+ (NSString *)getServerTypeString:(ISEServerType)serverType;

/*!
 Static method used to get the default INSITEO server URL from a given server type.
 @param server The wanted server type.
 @result The server URL to use.
 */
+ (NSString *)getBaseURL:(ISEServerType)server;

/*!
 Static method used to get the default INSITEO directory path.
 @result The default INSITEO directory path.
 */
+ (NSString *)getRootDirectoryPath;

/*
 Internal method used to launch the analytics service automatically.
 */
- (void)tryAutoStartAnalytics;

/*!
 Method called to get an NSString representing the site version.
 @return Related NSString (ex: @"56/1/fr").
 */
- (NSString *)siteVersionString;

/*
 Method used to load the initialization HTTP content from INSITEO servers.
 @param language Language to use.
 @param forceDownload Boolean used to know if we force the download of packages even if the application is up to date.
 @param serverType INSITEO server type.
 @param renderMode Wanted render mode.
 @return An ISInsiteoError object (could be nil).
 */
- (ISInsiteoError *)loadInitContentOverHttpWithLanguage:(NSString *)language andForceDownload:(Boolean)forceDownload andServerType:(ISEServerType)serverType andRenderMode:(ISERenderMode)renderMode;

#pragma mark - Start

/*!
 Method used to initialize the API.
 @param serverType INSITEO server type.
 @param siteId The site identifier to use.
 @param language The language to use.
 @param startHandler The API initialization handler to call.
 @param updateHandler The API update handler to call.
 @param updateProgressHandler The API update progress handler to call.
 @param renderMode Wanted render mode.
 @param applicationVersion The application version to use.
 @param forceDownload Boolean used to know if we force the download of packages even if the application is up to date.
 @param analyticsAutoStart Boolean used to know if we can start analytics automatically.
 @param serverUrl Specific server URL to use.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)startWithServerType:(ISEServerType)serverType andSiteId:(int)siteId andLanguage:(NSString *)language andStartHandler:(ISInitProviderStartHandler)startHandler andUpdateHandler:(ISInitProviderUpdateHandler)updateHandler andUpdateProgressHandler:(ISInitProviderUpdateProgressHandler)updateProgressHandler andRenderMode:(ISERenderMode)renderMode andApplicationVersion:(int)applicationVersion andForceDownload:(Boolean)forceDownload andAnalyticsAutoStart:(Boolean)analyticsAutoStart andServerUrl:(NSString *)serverUrl;

/*!
 Method used to initialize the API.
 @param serverType INSITEO server type.
 @param siteId The site identifier to use.
 @param language The language to use.
 @param startHandler The API initialization handler to call.
 @param updateHandler The API update handler to call.
 @param updateProgressHandler The API update progress handler to call.
 @param renderMode Wanted render mode.
 @param applicationVersion The application version to use.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)startWithServerType:(ISEServerType)serverType andSiteId:(int)siteId andLanguage:(NSString *)language andStartHandler:(ISInitProviderStartHandler)startHandler andUpdateHandler:(ISInitProviderUpdateHandler)updateHandler andUpdateProgressHandler:(ISInitProviderUpdateProgressHandler)updateProgressHandler andRenderMode:(ISERenderMode)renderMode andApplicationVersion:(int)applicationVersion;

/*!
 Method used to initialize the API.
 @param serverType INSITEO server type.
 @param siteId The site identifier to use.
 @param language The language to use.
 @param startHandler The API initialization handler to call.
 @param updateHandler The API update handler to call.
 @param updateProgressHandler The API update progress handler to call.
 @param renderMode Wanted render mode.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)startWithServerType:(ISEServerType)serverType andSiteId:(int)siteId andLanguage:(NSString *)language andStartHandler:(ISInitProviderStartHandler)startHandler andUpdateHandler:(ISInitProviderUpdateHandler)updateHandler andUpdateProgressHandler:(ISInitProviderUpdateProgressHandler)updateProgressHandler andRenderMode:(ISERenderMode)renderMode;

/*!
 Method used to initialize the API.
 @param serverType INSITEO server type.
 @param siteId The site identifier to use.
 @param language The language to use.
 @param startHandler The API initialization handler to call.
 @param renderMode Wanted render mode.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)startWithServerType:(ISEServerType)serverType andSiteId:(int)siteId andLanguage:(NSString *)language andStartHandler:(ISInitProviderStartHandler)startHandler andRenderMode:(ISERenderMode)renderMode;

#pragma mark - Update

/*!
 Method used to update application packages.
 @param updateHandler The API update handler to call.
 @param updateProgressHandler The API update progress handler to call.
 @param wantedPackages An array of ISPackage that need to be updated.
 @param force Boolean used to know if we force the download of all packages.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)updateWithUpdateHandler:(ISInitProviderUpdateHandler)updateHandler andUpdateProgressHandler:(ISInitProviderUpdateProgressHandler)updateProgressHandler andWantedPackages:(NSArray *)wantedPackages andForce:(Boolean)force;

/*!
 Method used to update application packages.
 @param updateHandler The API update handler to call.
 @param updateProgressHandler The API update progress handler to call.
 @param wantedPackages An array of ISPackage that need to be updated.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)updateWithUpdateHandler:(ISInitProviderUpdateHandler)updateHandler andUpdateProgressHandler:(ISInitProviderUpdateProgressHandler)updateProgressHandler andWantedPackages:(NSArray *)wantedPackages;

/*!
 Method used to update application packages.
 @param updateHandler The API update handler to call.
 @param updateProgressHandler The API update progress handler to call.
 @return a task that can be cancelled.
 */
- (id<ISPCancelable>)updateWithUpdateHandler:(ISInitProviderUpdateHandler)updateHandler andUpdateProgressHandler:(ISInitProviderUpdateProgressHandler)updateProgressHandler;

#pragma mark - Package

/*!
 Method used to know if the application has a specific package type stored.
 @param packageType Package type to test.
 @param siteId Site identifier to consider.
 @param applicationVersion Application version to consider.
 @param language Language to consider.
 @param serverType INSITEO server type to communicate with.
 @return <b>YES</b> if it exists, otherwise <b>NO</b>.
 */
- (Boolean)hasPackageWithPackageType:(ISPackageType)packageType andSiteId:(int)siteId andApplicationVersion:(int)applicationVersion andLanguage:(NSString *)language andServerType:(ISEServerType)serverType;

/*!
 Method used to know if the application has a specific package type stored.
 @param packageType Package type to test.
 @param siteId Site identifier to consider.
 @param applicationVersion Application version to consider.
 @param language Language to consider.
 @return <b>YES</b> if it exists, otherwise <b>NO</b>.
 */
- (Boolean)hasPackageWithPackageType:(ISPackageType)packageType andSiteId:(int)siteId andApplicationVersion:(int)applicationVersion andLanguage:(NSString *)language;

/*!
 Method used to know if the application has a specific package type stored. (In this case we use last application state : siteId, applicationVersion, language).
 @param packageType Package type to test.
 @param serverType INSITEO server type to communicate with.
 @return <b>YES</b> if it exists, otherwise <b>NO</b>.
 */
- (Boolean)hasPackageWithPackageType:(ISPackageType)packageType andServerType:(ISEServerType)serverType;

/*!
 Method used to know if the application has a specific package type stored. (In this case we use last application state : siteId, applicationVersion, language).
 @param packageType Package type to test.
 @return <b>YES</b> if it exists, otherwise <b>NO</b>.
 */
- (Boolean)hasPackageWithPackageType:(ISPackageType)packageType;

/*
 Application should not use this method directly.
 Intern method called to get the real absolute path of a package.
 @param packageType Package type to test.
 @return Absolute package path.
 */
- (NSString *)getPathWithPackageType:(ISPackageType)packageType andReal:(Boolean)real;

/*!
 Method used to get the absolute path of a package.
 @param packageType Package type to test.
 @return Absolute package path.
 */
- (NSString *)getPathWithPackageType:(ISPackageType)packageType;

/*!
 Method used to get current version of a package.
 @param packageType Package type to test.
 @return The current package version.
 */
- (int)getCurrentPackageVersionWithPackageType:(ISPackageType)packageType;

/*!
 Method used to know which new packages are available.
 @return An array which contains all new ISPackage.
 */
- (NSArray *)getNewPackages;

#pragma mark - MapData

/*!
 Method called to get a specific map with its identifier.
 @param mapId Wanted map identifier.
 @return The related ISMap.
 */
- (ISMap *)getMapWithMapId:(int)mapId;

/*!
 Method called to get a specific zone with its identifier.
 @param zoneId Wanted zone identifier.
 @return The related ISZone.
 */
- (ISZone *)getZoneWithId:(int)zoneId;

/*!
 Method called to get all the zones into a given map.
 @param mapId Wanted map identifier.
 @return An array of ISZone.
 */
- (NSArray *)getZonesWithMapId:(int)mapId;

#pragma mark - Database

/*
 Application should not use this method directly.
 Register a database helper that will be automatically opened and closed by InitProvider.
 @param dbHelper The DB helper to register.
 @param packageType The DB helper key used to find it.
 */
- (void)registerDbHelper:(ISRODBHelper *)dbHelper andPackageType:(NSString *)packageType;

#pragma mark - Notify

/*
 Intern.
 */
- (void)notifyOnDataUpdateDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error;

@end