enum {
#define LOOKUP_SET(id, num, type) FOO_ ## id = num,
#include "lookup/general.lst"
};

static table rcv_lookup {
#define LOOKUP_SET(id, num, type) { FOO_ ## id, table::type, #id },
#include "lookup/rcv.lst"
#include "lookup/general.lst"
};

static table snd_lookup {
#define LOOKUP_SET(id, num, type) { FOO_ ## id, table::type, #id },
#include "lookup/snd.lst"
#include "lookup/general.lst"
};

