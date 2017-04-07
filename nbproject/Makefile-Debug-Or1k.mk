#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=or1k-linux-musl-gcc
CCC=or1k-linux-musl-g++
CXX=or1k-linux-musl-g++
FC=gfortran
AS=or1k-linux-musl-as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug-Or1k
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/DelegateTest/DelegateTest.o \
	${OBJECTDIR}/src/LithpAtom.o \
	${OBJECTDIR}/src/LithpDict.o \
	${OBJECTDIR}/src/LithpExceptions.o \
	${OBJECTDIR}/src/LithpInteger.o \
	${OBJECTDIR}/src/LithpList.o \
	${OBJECTDIR}/src/LithpOpChain.o \
	${OBJECTDIR}/src/LithpPrimitive.o \
	${OBJECTDIR}/src/LithpString.o \
	${OBJECTDIR}/src/OpChainTypes/LithpFunctionCall.o \
	${OBJECTDIR}/src/OpChainTypes/LithpLiteral.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/lithp.exe

${CND_DISTDIR}/${CND_CONF}/lithp.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}
	or1k-linux-musl-g++ -o ${CND_DISTDIR}/${CND_CONF}/lithp ${OBJECTFILES} ${LDLIBSOPTIONS} -static -s

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/DelegateTest/DelegateTest.o: src/DelegateTest/DelegateTest.cpp
	${MKDIR} -p ${OBJECTDIR}/src/DelegateTest
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/DelegateTest/DelegateTest.o src/DelegateTest/DelegateTest.cpp

${OBJECTDIR}/src/LithpAtom.o: src/LithpAtom.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpAtom.o src/LithpAtom.cpp

${OBJECTDIR}/src/LithpDict.o: src/LithpDict.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpDict.o src/LithpDict.cpp

${OBJECTDIR}/src/LithpExceptions.o: src/LithpExceptions.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpExceptions.o src/LithpExceptions.cpp

${OBJECTDIR}/src/LithpInteger.o: src/LithpInteger.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpInteger.o src/LithpInteger.cpp

${OBJECTDIR}/src/LithpList.o: src/LithpList.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpList.o src/LithpList.cpp

${OBJECTDIR}/src/LithpOpChain.o: src/LithpOpChain.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpOpChain.o src/LithpOpChain.cpp

${OBJECTDIR}/src/LithpPrimitive.o: src/LithpPrimitive.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpPrimitive.o src/LithpPrimitive.cpp

${OBJECTDIR}/src/LithpString.o: src/LithpString.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpString.o src/LithpString.cpp

${OBJECTDIR}/src/OpChainTypes/LithpFunctionCall.o: src/OpChainTypes/LithpFunctionCall.cpp
	${MKDIR} -p ${OBJECTDIR}/src/OpChainTypes
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OpChainTypes/LithpFunctionCall.o src/OpChainTypes/LithpFunctionCall.cpp

${OBJECTDIR}/src/OpChainTypes/LithpLiteral.o: src/OpChainTypes/LithpLiteral.cpp
	${MKDIR} -p ${OBJECTDIR}/src/OpChainTypes
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -Iinclude/ -Icontrib/delegates/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OpChainTypes/LithpLiteral.o src/OpChainTypes/LithpLiteral.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
