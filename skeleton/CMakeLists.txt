add_library(SkeletonPass MODULE
    # List your source files here.
    Skeleton.cpp
)

add_library(ShackletonPass MODULE
    # List your source files here.
    Shackleton.cpp
)

add_library(SheltonPass MODULE
    # List your source files here.
    Shelton.cpp
)

#add_library(StiltonPass MODULE
#    # List your source files here.
#    Stilton.cpp
#)

# Use C++11 to compile our pass (i.e., supply -std=c++11).
target_compile_features(SkeletonPass PRIVATE cxx_range_for cxx_auto_type)
target_compile_features(ShackletonPass PRIVATE cxx_range_for cxx_auto_type)
target_compile_features(SheltonPass PRIVATE cxx_range_for cxx_auto_type)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(SkeletonPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
set_target_properties(ShackletonPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
set_target_properties(SheltonPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(SkeletonPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
    set_target_properties(ShackletonPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
    set_target_properties(SheltonPass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
