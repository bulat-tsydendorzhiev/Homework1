#pragma once

// ok: everything is alright;
// scanError: value scanning failed;
// outOfMemory: lack of memory became
typedef enum
{
    ok,
    scanError,
    outOfMemory
} ErrorCodes;

// Console
ErrorCodes runProgram(void);
