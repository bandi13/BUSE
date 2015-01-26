#ifndef COMMONINCLUDES_H
#define COMMONINCLUDES_H

#ifdef DEBUG
#define DEBUGCODE(X) do { X; } while(0);
#else
#define DEBUGCODE(X)
#endif

#define UNUSED(expr) (void)(expr)

#endif
