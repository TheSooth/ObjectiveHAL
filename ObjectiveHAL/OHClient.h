//
//  OHClient.h
//  ObjectiveHAL
//
//  Created by Bennett Smith on 8/4/13.
//  Copyright (c) 2013 Mobile App Machine LLC. All rights reserved.
//

#import "AFHTTPClient.h"

@class OHLink;
@class OHResource;

typedef void (^OHLinkTraversalHandler)(NSString *rel, OHResource *targetResource, NSError *error);
typedef void (^OHCompletionHandler)(NSString *rel);

/** Interaction with AFNetworking
 */
@interface OHClient : AFHTTPClient

/**
 Monitor this using KVO to determine when the root resource has been successfully
 retrieved from the server.
 */
@property (nonatomic, assign, readonly, getter = isRootObjectAvailable) BOOL rootObjectAvailable;

/** The root (top-level) object retrieved from the server.
 */
@property (nonatomic, strong) OHResource *rootObject;

/** Initialize the OHClient.
 @param url Base URL for the service.
 */
- (id)initWithBaseURL:(NSURL *)url;

/** Fetch the root (top-level) object from the server.
 Any additional navigation through the objects on the server is done
 using methods of the OHResource class.
 
 @param path Path to root resource.
 */
- (void)fetchRootObjectFromPath:(NSString *)path;

/** Fetch a resource from a specific path on the server.
 @param path Path to the resource. Can be absolute or relative to base url.
 @param handler The traversal handler, called for the target resource.
 @param completion The completion handler, called once the resource traversal has completed.
 */
- (void)fetchResourceFromPath:(NSString *)path traversalHandler:(OHLinkTraversalHandler)handler completionHandler:(OHCompletionHandler)completion;

/** Traverse links for a relation on a given resource.
 @param links An array of OHLink objects, each of which will be traversed.
 @param rel The link relation that these traversal operations are a part of.
 @param resource The resource the traversal is being done for.
 @param handler The traversal handler, called for each target resource.
 @param completion The completion handler, called once all traversal operations have completed.
 */
- (void)traverseLinks:(NSArray *)links forRel:(NSString *)rel inResource:(OHResource *)resource traversalHandler:(OHLinkTraversalHandler)handler completionHandler:(OHCompletionHandler)completion;

@end
