//
//  ItineraryManager.h
//  LocationAPI
//
//  Created by INSITEO on 10/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISItineraryProvider.h
 ISItineraryProvider
 */

#import <Foundation/Foundation.h>

#import "ISLocationProvider.h"
#import "ISItineraryRequest.h"
#import "ISItineraryOptimizedRequest.h"

@class EmbeddedItineraryProvider;

/*!
 Class used to manage Itinerary requests.
 */
@interface ISItineraryProvider : NSObject <ISPLbsModule> {
    
@protected
    
    //Boolean used to know if we have to notify on instructions update event
    Boolean m_instructionsUpdateNotifyEnabled;
    //Embedded itinerary provider
    EmbeddedItineraryProvider * m_embeddedItineraryProvider;
    //Last location received
    ISLocation * m_lastLocation;
    //Last itinerary computed
    ISItinerary * m_lastItinerary;
    //Intern session identifier (used to combine location and itinerary information)
    NSNumber * m_sessionId;
    
#pragma mark - Internal
    
    //Last Itinerary request
    ISItineraryBaseRequest * m_lastItineraryRequest;
    
    NSLock * m_embeddedLock;
}

/*!
 Boolean used to know if we have to notify on instructions update event.
 */
@property (nonatomic, readwrite) Boolean instructionsUpdateNotifyEnabled;

/*!
 Embedded itinerary provider.
 */
@property (nonatomic, retain) EmbeddedItineraryProvider * embeddedItineraryProvider;

/*!
 Last location received.
 */
@property (nonatomic, retain) ISLocation * lastLocation;

/*!
 Last itinerary computed.
 */
@property (nonatomic, retain) ISItinerary * lastItinerary;

/*!
 Intern session identifier (used to combine location and itinerary information).
 */
@property (nonatomic, retain) NSNumber * sessionId;


/*!
 Static method used to get the last location identifier.
 @return Current location get id.
 */
+ (int)getLocationId;

/*!
 Method used to get a route from the user current location.
 @param endPoint Itinerary request end point.
 @param endMapId Itinerary request end map identifier.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute the route for disabled people.
 @return Related request.
 */
- (ISItineraryRequest *)requestItineraryFromCurrentLocationWithEndPoint:(CGPoint)endPoint andEndMapId:(int)endMapId andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method used to get a route from the user current location.
 @param endPositions Itinerary request end position array.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute the route for disabled people.
 @return Related request.
 */
- (ISItineraryRequest *)requestItineraryFromCurrentLocationWithEndPositions:(NSArray *)endPositions andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method used to get a route to the user current location.
 @param startPoint Itinerary request start point.
 @param startMapId Itinerary request start map identifier.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute the route for disabled people.
 @return Related request.
 */
- (ISItineraryRequest *)requestItineraryToCurrentLocationWithStartPoint:(CGPoint)startPoint andStartMapId:(int)startMapId andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method used to get a route to the user current location.
 @param startPositions Itinerary request start position array.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute the route for disabled people.
 @return Related request.
 */
- (ISItineraryRequest *)requestItineraryToCurrentLocationWithStartPositions:(NSArray *)startPositions andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method used to get a route between two points.
 @param startPoint Itinerary request start point.
 @param startMapId Itinerary request start map id.
 @param endPoint Itinerary request end point.
 @param endMapId Itinerary request end map id.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute the route for disabled people.
 @return Related request.
 */
- (ISItineraryRequest *)requestItineraryWithStartPoint:(CGPoint)startPoint andStartMapId:(int)startMapId andEndPoint:(CGPoint)endPoint andEndMapId:(int)endMapId andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method used to get a route between two points.
 @param startPositions Itinerary request start positions array.
 @param endPositions Itinerary request end positions array.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute the route for disabled people.
 @return Related request (nil if error).
 */
- (ISItineraryRequest *)requestItineraryWithStartPositions:(NSMutableArray *)startPositions andEndPositions:(NSMutableArray *)endPositions andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method used to get an optimized route between several points.
 @param waypoints Waypoints to pass through.
 @param mode Algorithm optimization mode.
 @param keepFirstPosition Boolean used to know if we treat the first position.
 @param keepLastPosition Boolean used to know if we treat the last position.
 @param listener Listener to notify for ISItineraryRequest events (succeeded, failed).
 @param pmr Boolean used to know if we compute a route for disabled people.
 @return Related request (nil if error).
 */
- (ISItineraryOptimizedRequest *)requestOptimizedItineraryWithWaypoints:(NSArray *)waypoints andOptimMode:(ISEOptimizationMode)mode andKeepFirstPosition:(Boolean)keepFirstPosition andKeepLastPosition:(Boolean)keepLastPosition andListener:(id<ISPItineraryRequestListener>)listener andPMR:(Boolean)pmr;

/*!
 Method called to update the last itinerary.
 @param itinerary Itinerary to use.
 */
- (void)updateItinerary:(ISItinerary *)itinerary;

/*!
 Method used to load all itinerary data to memory, this way the 1st itinerary request will be faster.
 */
- (void)preloadItineraryGraph ;

/*!
 Intern method used to lock the itinerary stuff.
*/
- (void)lock;

/*!
 Intern method used to unlock the itinerary stuff.
 */
- (void)unlock;

@end