// auto generated by go tool dist
// goos=windows goarch=amd64


#include "runtime.h"
#include "arch_GOARCH.h"
#include "type.h"
#include "typekind.h"
#include "malloc.h"
#include "race.h"
#include "stack.h"
#include "../../cmd/ld/textflag.h"

#line 15 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
enum 
{ 
debug = 0 
} ; 
#line 20 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
static void makeslice1 ( SliceType* , intgo , intgo , Slice* ) ; 
static void growslice1 ( SliceType* , Slice , intgo , Slice * ) ; 
void
runtime·makeslice(SliceType* t, int64 len, int64 cap, Slice ret)
{
	ret.array = 0;
	ret.len = 0;
	ret.cap = 0;
	FLUSH(&ret);
#line 24 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"

	// NOTE: The len > MaxMem/elemsize check here is not strictly necessary,
	// but it produces a 'len out of range' error instead of a 'cap out of range' error
	// when someone does make([]T, bignumber). 'cap out of range' is true too,
	// but since the cap is only being supplied implicitly, saying len is clearer.
	// See issue 4085.
	if(len < 0 || (intgo)len != len || t->elem->size > 0 && len > MaxMem / t->elem->size)
		runtime·panicstring("makeslice: len out of range");

	if(cap < len || (intgo)cap != cap || t->elem->size > 0 && cap > MaxMem / t->elem->size)
		runtime·panicstring("makeslice: cap out of range");

	makeslice1(t, len, cap, &ret);

	if(debug) {
		runtime·printf("makeslice(%S, %D, %D); ret=",
			*t->string, len, cap);
		runtime·printslice(ret);
	}
	FLUSH(&ret);
}

#line 48 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
uintptr runtime·zerobase; 
#line 50 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
static void 
makeslice1 ( SliceType *t , intgo len , intgo cap , Slice *ret ) 
{ 
ret->len = len; 
ret->cap = cap; 
ret->array = runtime·cnewarray ( t->elem , cap ) ; 
} 
void
runtime·growslice(SliceType* t, Slice old, int64 n, Slice ret)
{
	ret.array = 0;
	ret.len = 0;
	ret.cap = 0;
	FLUSH(&ret);
#line 59 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"

	int64 cap;
	void *pc;

	if(n < 1)
		runtime·panicstring("growslice: invalid n");

	cap = old.cap + n;

	if((intgo)cap != cap || cap < (int64)old.cap || (t->elem->size > 0 && cap > MaxMem/t->elem->size))
		runtime·panicstring("growslice: cap out of range");

	if(raceenabled) {
		pc = runtime·getcallerpc(&t);
		runtime·racereadrangepc(old.array, old.len*t->elem->size, pc, runtime·growslice);
	}

	growslice1(t, old, cap, &ret);

	if(debug) {
		runtime·printf("growslice(%S,", *t->string);
		runtime·printslice(old);
		runtime·printf(", new cap=%D) =", cap);
		runtime·printslice(ret);
	}
	FLUSH(&ret);
}

#line 86 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
static void 
growslice1 ( SliceType *t , Slice x , intgo newcap , Slice *ret ) 
{ 
intgo newcap1; 
uintptr capmem , lenmem; 
int32 flag; 
Type *typ; 
#line 94 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
typ = t->elem; 
if ( typ->size == 0 ) { 
*ret = x; 
ret->cap = newcap; 
return; 
} 
#line 101 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
newcap1 = x.cap; 
#line 107 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
if ( newcap1+newcap1 < newcap ) 
newcap1 = newcap; 
else { 
do { 
if ( x.len < 1024 ) 
newcap1 += newcap1; 
else 
newcap1 += newcap1/4; 
} while ( newcap1 < newcap ) ; 
} 
#line 118 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
if ( newcap1 > MaxMem/typ->size ) 
runtime·panicstring ( "growslice: cap out of range" ) ; 
capmem = runtime·roundupsize ( newcap1*typ->size ) ; 
flag = 0; 
#line 123 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"
if ( typ->kind&KindNoPointers ) 
flag = FlagNoScan|FlagNoZero; 
ret->array = runtime·mallocgc ( capmem , ( uintptr ) typ|TypeInfo_Array , flag ) ; 
ret->len = x.len; 
ret->cap = capmem/typ->size; 
lenmem = x.len*typ->size; 
runtime·memmove ( ret->array , x.array , lenmem ) ; 
if ( typ->kind&KindNoPointers ) 
runtime·memclr ( ret->array+lenmem , capmem-lenmem ) ; 
} 
#pragma textflag NOSPLIT

void
runtime·copy(Slice to, Slice fm, uintptr width, intgo ret)
{
	ret = 0;
	FLUSH(&ret);
#line 135 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"

	void *pc;

	if(fm.len == 0 || to.len == 0 || width == 0) {
		ret = 0;
		goto out;
	}

	ret = fm.len;
	if(to.len < ret)
		ret = to.len;

	if(raceenabled) {
		pc = runtime·getcallerpc(&to);
		runtime·racewriterangepc(to.array, ret*width, pc, runtime·copy);
		runtime·racereadrangepc(fm.array, ret*width, pc, runtime·copy);
	}

	if(ret == 1 && width == 1) {	// common case worth about 2x to do here
		*to.array = *fm.array;	// known to be a byte pointer
	} else {
		runtime·memmove(to.array, fm.array, ret*width);
	}

out:

	if(debug) {
		runtime·prints("main·copy: to=");
		runtime·printslice(to);
		runtime·prints("; fm=");
		runtime·printslice(fm);
		runtime·prints("; width=");
		runtime·printint(width);
		runtime·prints("; ret=");
		runtime·printint(ret);
		runtime·prints("\n");
	}
	FLUSH(&ret);
}

#pragma textflag NOSPLIT
void
runtime·slicestringcopy(Slice to, String fm, intgo ret)
{
	ret = 0;
	FLUSH(&ret);
#line 175 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"

	void *pc;

	if(fm.len == 0 || to.len == 0) {
		ret = 0;
		goto out;
	}

	ret = fm.len;
	if(to.len < ret)
		ret = to.len;

	if(raceenabled) {
		pc = runtime·getcallerpc(&to);
		runtime·racewriterangepc(to.array, ret, pc, runtime·slicestringcopy);
	}

	runtime·memmove(to.array, fm.str, ret);

out:;
	FLUSH(&ret);
}
void
runtime·printslice(Slice a)
{
#line 197 "C:\Users\ADMINI~1\AppData\Local\Temp\2\makerelease686069423\go\src\pkg\runtime\slice.goc"

	runtime·prints("[");
	runtime·printint(a.len);
	runtime·prints("/");
	runtime·printint(a.cap);
	runtime·prints("]");
	runtime·printpointer(a.array);
}
