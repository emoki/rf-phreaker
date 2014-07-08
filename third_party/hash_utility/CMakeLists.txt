project (hash_utility)

# hash_utility version number.
# TODO - finish this when you have time!
set (hash_utility_VERSION_MAJOR 1)
set (hash_utility_VERSION_MINOR 0)
set (hash_utility_VERSION_PATCH 0)
set (hash_utility_VERSION_TWEAK 0)

# Set the source files.
set (hash_utility_SRCS 
	hash_utility/crc32.cpp
	hash_utility/crc32.h
	hash_utility/digest.cpp
	hash_utility/hash.h
	hash_utility/keccak.cpp
	hash_utility/keccak.h
	hash_utility/md5.cpp
	hash_utility/md5.h
	hash_utility/sha1.cpp
	hash_utility/sha1.h
	hash_utility/sha256.cpp
	hash_utility/sha256.h
	hash_utility/sha3.cpp
	hash_utility/sha3.h)

add_library (hash_utility STATIC ${hash_utility_SRCS})
