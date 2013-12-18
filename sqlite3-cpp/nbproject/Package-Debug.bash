#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build
CND_DLIB_EXT=so
NBTMPDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsqlite3-cpp.${CND_DLIB_EXT}
OUTPUT_BASENAME=libsqlite3-cpp.${CND_DLIB_EXT}
PACKAGE_TOP_DIR=/usr/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${NBTMPDIR}
mkdir -p ${NBTMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/lib"
copyFileToTmpDir "${OUTPUT_PATH}" "${NBTMPDIR}/${PACKAGE_TOP_DIR}lib/${OUTPUT_BASENAME}" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include"
copyFileToTmpDir "include/Sqlite3.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/Sqlite3.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Column.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Column.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Statement.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Statement.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Query.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Query.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Transaction.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Transaction.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Exception.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Exception.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Database.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Database.hpp" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}//usr/include/sqlite3-cpp"
copyFileToTmpDir "include/sqlite3-cpp/Row.hpp" "${NBTMPDIR}/${PACKAGE_TOP_DIR}include/sqlite3-cpp/Row.hpp" 0644


# Create control file
cd "${TOP}"
CONTROL_FILE=${NBTMPDIR}/DEBIAN/control
rm -f ${CONTROL_FILE}
mkdir -p ${NBTMPDIR}/DEBIAN

cd "${TOP}"
echo 'Package: libsqlite3-cpp.so' >> ${CONTROL_FILE}
echo 'Version: 1.0' >> ${CONTROL_FILE}
echo 'Architecture: amd64' >> ${CONTROL_FILE}
echo 'Maintainer: Augusto Campos (augcampos)' >> ${CONTROL_FILE}
echo 'Description: Sqlite 3 C++ Wrapper' >> ${CONTROL_FILE}

# Create Debian Package
cd "${TOP}"
cd "${NBTMPDIR}/.."
dpkg-deb  --build ${TMPDIRNAME}
checkReturnCode
cd "${TOP}"
mkdir -p  ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
mv ${NBTMPDIR}.deb ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/libsqlite3-cpp.so.deb
checkReturnCode
echo Debian: ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/libsqlite3-cpp.so.deb

# Cleanup
cd "${TOP}"
rm -rf ${NBTMPDIR}
