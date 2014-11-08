#ifndef __ATI__
#define __ATI__


/* Control Transfer Instructions      */
/*                                    */
/* CTI_1:  JMP   JCC                  */  #include "jcc/jcc.h"
/*         (-) JMP  -> ATI/ATI_1      */
/*                                    */
/* CTI_2:  CALL  LEAVE  RET           */  #include "CTI_2/CTI_2.h"
/*         (-) CALL -> ATI/ATI_1      */



#endif