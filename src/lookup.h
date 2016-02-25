enum {
#define LOOKUP_SET(id, name, num, type, write) id = num,
#include "lookup/map.lst"
#undef LOOKUP_SET
};

static table lookup {
#define LOOKUP_SET(id, name, num, type, write) { id, table::type, table::write, #name, #id},
#include "lookup/map.lst"
#undef LOOKUP_SET
};

