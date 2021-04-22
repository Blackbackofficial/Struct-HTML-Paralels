file(REMOVE_RECURSE
  "CMakeFiles/cppcheck"
  "CMakeFiles/cppcheck-complete"
  "external/cppcheck/stamp/cppcheck-build"
  "external/cppcheck/stamp/cppcheck-configure"
  "external/cppcheck/stamp/cppcheck-download"
  "external/cppcheck/stamp/cppcheck-install"
  "external/cppcheck/stamp/cppcheck-mkdir"
  "external/cppcheck/stamp/cppcheck-patch"
  "external/cppcheck/stamp/cppcheck-update"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/cppcheck.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
