set(TARGET hvms)

add_compile_options(-mcmodel=medany)

add_executable(${TARGET})

target_setup_cpp(${TARGET})

target_sources(
    ${TARGET}
    PRIVATE
        main.cpp
)

target_compile_options(${TARGET} PRIVATE
    -Os                     # Optimize for size
    -ffunction-sections     # Put each function in its own section
    -fdata-sections        # Put each data item in its own section
    -fno-exceptions
    -fno-rtti
    -fno-use-cxa-atexit
    -fno-threadsafe-statics
)

target_link_options(${TARGET} PRIVATE
    -Wl,--gc-sections      # Remove unused sections
    -nostartfiles
)