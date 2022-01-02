check_include_file( "stdint.h" HAVE_STDINT_H )
if( NOT HAVE_STDINT_H )
	message( FATAL_ERROR "Environment Not POSIX Compliant" )
endif( NOT HAVE_STDINT_H )

check_source_compiles( C 
	"#include <stdint.h>
	int main(){ uint64_t uint64; return 0; }" 
	HAVE_UINT64_T
)
if( NOT HAVE_UINT64_T )
	message( SEND_ERROR )
	message( NOTICE "If you are seeing this message:" )
	message( NOTICE "  - ON 64-BIT MACHINE:" )
	message( NOTICE "      I. Fire your Administrator:" )
	message( NOTICE "           If they where competent, they would have installed your" )
	message( NOTICE "             compiler suite correctly the first time and you would not be seeing" )
	message( NOTICE "             this message." )
	message( NOTICE "     II. Have your NEW Administrator *clean-install* your compiler suite:" )
	message( NOTICE "           Again, this is probably an installation issue: " )
	message( NOTICE "             e.g. a 32-bit compiler suite installed on a 64-bit machine." )
	message( NOTICE "             And if that's the case, and you didn't catch it, then fire yourself" )
	message( NOTICE "             because you have no business masquerading as a Software Developer." )
	message( NOTICE "           As far as clean-installing: do as you will.  A quality Admin will" )
	message( NOTICE "             do this instinctivly beacause it is a sure way to sanitize" )
	message( NOTICE "             the environment in order to prevent a repeat performace or worse." )
	message( NOTICE "  - IF ISSUE PERSISTS [ON 64-BIT MACHINE]" )
	message( NOTICE "    III. Appologize to your OLD Admin and get customer support on the phone:" )
	message( NOTICE "           At this point in the troubleshooting proceess we have eliminated" )
	message( NOTICE "             the possibility of an `ID10T' Error and there is a real problem:" )
	message( NOTICE "             - Either the package provider really shpxrq hc and gave you" )
	message( NOTICE "                 the wrong files," )
	message( NOTICE "             - Or the upstream developer willfully neglected to provide" )
	message( NOTICE "                 the standard data types emplyed by this program." )
	message( NOTICE "           In any case, do this is in the off-chance that the upstream developer" )
	message( NOTICE "             (or maintainer) might hold any interest in retaining clientele" )
	message( NOTICE "             as demonstraited by an immediate and ernest rectification of their" )
	message( NOTICE "             error.  However, the modern business model embodying" )
	message( NOTICE "             the \"take it or leave it\" approach in regaurds to sales tactics," )
	message( NOTICE "             you will most likely need to" )
	message( NOTICE "     IV. Abbandon your current compiler suite and patronize a more honest one." )
	message( NOTICE "           This project is developed using GCC and is garrenteed to compile in" )
	message( NOTICE "             the standard GCC environment." )
	message( NOTICE "           THIS MESSAGE IS IN NO WAY INTEDED AS A VOUCHER PERTAINING TO" )
	message( NOTICE "             THE INTEGRITY OF GNU OR IT'S AFFILIATES.  However, it is understood" )
	message( NOTICE "             that GNU strives to maintain a degree of POSIX and C/C++ compliance" )
	message( NOTICE "             in addition to such extentions which they have seen fit to impliment." )
	message( NOTICE "           ================================ NOTICE ==============================" )
	message( NOTICE "           * IT IS THE *OPINION* OF THIS DEVELOPER THAT CERTAIN ISO FEATURES    *" )
	message( NOTICE "           *   OF C AND C++ OUGHT NOT BE IMPLIMENTED BY *ANY* COMPILER SUITE,   *" )
	message( NOTICE "           *   PARTICULARLY THOSE REGARDING THE ADDITION OF REFLECTION TO THESE *" )
	message( NOTICE "           *   LANGUAGES.  Such proposals have been born from users of          *" )
	message( NOTICE "           *   higher-level languages who cannot be bothered to learn the C-way *" )
	message( NOTICE "           *   of doing things and thus [thoughtlessly] propose such features   *" )
	message( NOTICE "           *   as would inevitably alter these lower-level languages in thier   *" )
	message( NOTICE "           *   useful course by requiring them to incorperate such as live      *" )
	message( NOTICE "           *   symbol tables thereby compelling such programs to operate in     *" )
	message( NOTICE "           *   Java-like VMs instead of on Bare Metal as they do traditionally; *" )
	message( NOTICE "           * This implimentation detail may not seem important to most          *" )
	message( NOTICE "           *   developers who deal strictly in business logic, but would prove  *" )
	message( NOTICE "           *   catastrophic to it's real users who write Kernels, Drivers, and  *" )
 	message( NOTICE "           *   other such Firemware such as those VMs and Interpreters they     *" )
	message( NOTICE "           *   have come to rely on.                                            *" )
	message( NOTICE "           ======================================================================" )
	message( NOTICE "           It is trusted by this developer that GNU, as a developer of such" )
	message( NOTICE "             Firmware including Linux, will ever bear such considerations in mind" )
	message( NOTICE "             as they selectively impliment new features." )
	message( NOTICE "  - ELSE [IF NOT ON 64-BIT MACHINE OR BETTER]" )
	message( NOTICE "      If there is any good reason to be using a 32, 16 or (God forbid it) 8-bit" )
	message( NOTICE "        architecture, check our feature request list and submit a support" )
	message( NOTICE "        request for your architecture if, -- and ONLY IF, -- that request has" )
	message( NOTICE "        not already been made." )
	message( NOTICE "      Under any other circumstance, -- e.g. failing on a better machine, --" )
	message( NOTICE "        submit a detailed bug report including system information so that we can" )
	message( NOTICE "        resolve the issue." )
	message( FATAL_ERROR "Non 64-bit architectures not supported" )
endif( NOT HAVE_UINT64_T )

add_library( journal SHARED
	ELF64.c
)

target_compile_features( journal PRIVATE
	c_static_assert
	c_variadic_macros
)

if( BCUNIT_FOUND )
	add_executable( JournalUnitTests
		bcunit/main.c
		bcunit/ELF64.c
	)

	target_compile_options( JournalUnitTests
		PRIVATE "SHELL:-iquote ${CMAKE_CURRENT_SOURCE_DIR}"
	)

	target_link_libraries( JournalUnitTests
		journal
		${BCUNIT_LIBRARIES}
	)

	add_custom_target( UnitTest_Journal
		COMMAND JournalUnitTests
	)

else( BCUNIT_FOUND )
	message( WARNING "Journal: Unit Tests Disabled: BCUnit REQUIRED" )
endif( BCUNIT_FOUND )

