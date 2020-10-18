#if !defined(STDMACRO_ARRAY_SIZE_H)
#define STDMACRO_ARRAY_SIZE_H

#if !defined(ARRAY_SIZE)
	#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

#endif /* STDMACRO_ARRAY_SIZE_H */
