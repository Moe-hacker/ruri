# See https://stackoverflow.com/questions/55641889/access-build-id-at-runtime
build_id_start = ADDR(.note.gnu.build-id);
build_id_end = ADDR(.note.gnu.build-id) + SIZEOF(.note.gnu.build-id);
