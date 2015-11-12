//
//  VCTUtilityMarco.h
//  operation
//
//  Created by Vincent on 15-1-27.
//
//

//Auto Create Singleton Macro
#define create_declare(type) + (type *)instance;

#define create_impl(type)                       \
static type *instance_ = nil;                   \
+ (type *)instance {                            \
    if (!instance_) {                           \
        instance_ = [[type alloc] init];        \
    }                                           \
    return instance_;                           \
}