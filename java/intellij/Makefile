# Based on the devel/intellij port from OpenBSD by
# Vadim Zhukov <zhuk@openbsd.org>

PORTNAME=	intellij
PORTVERSION=	2022.3.2
CATEGORIES=	java devel
MASTER_SITES=	https://download-cf.jetbrains.com/idea/
DISTNAME=	ideaIC-${PORTVERSION}
DIST_SUBDIR=	jetbrains

MAINTAINER=	vishwin@FreeBSD.org
COMMENT=	IntelliJ IDEA Community Edition
WWW=		https://www.jetbrains.com/idea/

LICENSE=	APACHE20

RUN_DEPENDS=	intellij-fsnotifier>0:java/intellij-fsnotifier \
		intellij-pty4j>=0.11.4:java/intellij-pty4j \
		lsof:sysutils/lsof

USES=		python:run shebangfix ssl

USE_JAVA=	yes
JAVA_VERSION=	18

SHEBANG_FILES= bin/restart.py

CONFLICTS=	idea intellij-ultimate

NO_ARCH=	yes
NO_ARCH_IGNORE=	libjansi.so
NO_BUILD=	yes

BUILD_TYPE=	IC
BUILD_VERSION=	223.8617.56
BUILD_MARKER=	${BUILD_TYPE}-${BUILD_VERSION}
PLIST_SUB=	BUILD_MARKER=${BUILD_MARKER}
WRKSRC=		${WRKDIR}/idea-${BUILD_MARKER}

SUB_FILES=	idea idea.desktop pkg-message



post-patch:
	@${REINPLACE_CMD} 's/x86_64/amd64/g' ${WRKSRC}/bin/idea.sh
# Linux/Windows/OS X only so remove them
	@${RM} -r \
		${WRKSRC}/bin/fsnotifier \
		${WRKSRC}/bin/fsnotifier64 \
		${WRKSRC}/bin/libdbm.so \
		${WRKSRC}/lib/pty4j-native/ \
		${WRKSRC}/plugins/android/resources/native/ \
		${WRKSRC}/plugins/cwm-plugin/quiche-native/ \
		${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/linux32/ \
		${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/linux64/ \
		${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/osx/ \
		${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/windows32/ \
		${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/windows64/ \
		${WRKSRC}/plugins/performanceTesting/bin/ \
		${WRKSRC}/plugins/webp/lib/libwebp/


do-install:
	${MKDIR} ${STAGEDIR}${DATADIR}
	@(cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR} \
		"! -name *\.bak ! -name *\.so ! -name *\.dll ! -name *\.dylib ! -name *\.pdb ! -name *\.sh")
	@(cd ${WRKSRC} && ${COPYTREE_BIN} . ${STAGEDIR}${DATADIR} "-name *\.sh")
	${INSTALL_LIB} ${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/freebsd32/libjansi.so \
		${STAGEDIR}${DATADIR}/plugins/maven/lib/maven3/lib/jansi-native/freebsd32/
	${INSTALL_LIB} ${WRKSRC}/plugins/maven/lib/maven3/lib/jansi-native/freebsd64/libjansi.so \
		${STAGEDIR}${DATADIR}/plugins/maven/lib/maven3/lib/jansi-native/freebsd64/
	${INSTALL_SCRIPT} ${WRKDIR}/idea ${STAGEDIR}${PREFIX}/bin/idea
	${INSTALL_MAN} ${FILESDIR}/idea.1 ${STAGEDIR}${PREFIX}/man/man1
	${INSTALL_DATA} ${WRKDIR}/idea.desktop ${STAGEDIR}${PREFIX}/share/applications/
# Use fsnotifier replacement provided by java/intellij-fsnotifier
	${ECHO} "idea.filewatcher.executable.path=${PREFIX}/intellij/bin/fsnotifier" >> ${STAGEDIR}${DATADIR}/bin/idea.properties
# Use pty4j replacement provided by java/intellij-pty4j
	${LN} -sf ../../../intellij/lib/libpty ${STAGEDIR}${DATADIR}/lib/pty4j-native
# Fix "Typeahead timeout is exceeded" error
	${ECHO} "action.aware.typeAhead=false" >> ${STAGEDIR}${DATADIR}/bin/idea.properties

.include <bsd.port.mk>
