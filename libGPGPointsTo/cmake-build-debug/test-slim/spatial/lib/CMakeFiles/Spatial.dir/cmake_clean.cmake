file(REMOVE_RECURSE
  "../../../lib/libSpatial.pdb"
  "../../../lib/libSpatial.so"
  "../../../lib/libSpatial.so.0"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/Spatial.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
