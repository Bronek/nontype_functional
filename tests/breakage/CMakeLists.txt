add_executable(run-breakage)
target_sources(run-breakage PRIVATE
 "main.cpp"
)
target_compile_options(run-breakage PRIVATE
    $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:-Wno-self-move>
    $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-fsized-deallocation>)
target_link_libraries(run-breakage PRIVATE nontype_functional)
set_target_properties(run-breakage PROPERTIES OUTPUT_NAME run)
