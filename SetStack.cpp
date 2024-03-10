// Copyright Eric Chauvin 2022



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html



#include "../LinuxApi/SetStack.h"
#include "../LinuxApi/Casting.h"

#include <sys/resource.h>



// This gets called in main.cpp before anything else
// is done.

bool SetStack::setit( const Uint64 setTo )
{
// struct rlimit {
//           rlim_t rlim_cur;  // Soft limit
//           rlim_t rlim_max;  // Hard limit
//           };


struct rlimit rl;

Int32 result = getrlimit( RLIMIT_STACK, &rl );
if( result != 0 ) // Error is -1.
  return false;

if( rl.rlim_cur < setTo )
  {
  rl.rlim_cur = setTo;
  result = setrlimit( RLIMIT_STACK, &rl );
  if (result != 0)
    return false;

  }

return true;
}





Int32 SetStack::getSize( void )
{
struct rlimit rl;

Int32 result = getrlimit( RLIMIT_STACK, &rl );
if( result != 0 )
  return 0;

return Casting::U64ToI32( rl.rlim_cur );
}
