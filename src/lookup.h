enum {
#define LOOKUP_SET(id, num, type) RCV_ ## id = num,
#include "lookup/rcv.lst"
#include "lookup/general.lst"
#undef LOOKUP_SET
#define LOOKUP_SET(id, num, type) SND_ ## id = num,
#include "lookup/snd.lst"
#include "lookup/general.lst"
#undef LOOKUP_SET
#define LOOKUP_SET(id, num, type) id = num,
#include "lookup/rcv.lst"
#include "lookup/snd.lst"
#include "lookup/general.lst"
#undef LOOKUP_SET
};

static table rcv_lookup {
#define LOOKUP_SET(id, num, type) { RCV_ ## id, table::type, #id },
#include "lookup/rcv.lst"
#include "lookup/general.lst"
#undef LOOKUP_SET
};

static table snd_lookup {
#define LOOKUP_SET(id, num, type) { SND_ ## id, table::type, #id },
#include "lookup/snd.lst"
#include "lookup/general.lst"
#undef LOOKUP_SET
};

