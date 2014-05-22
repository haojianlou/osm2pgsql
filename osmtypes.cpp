
#include "osmtypes.hpp"
#include "middle.hpp"
#include "output.hpp"


osmdata_t::osmdata_t(middle_t* mid_, output_t* out_): mid(mid_), out(out_)
{
}

osmdata_t::~osmdata_t()
{
}

int osmdata_t::node_add(osmid_t id, double lat, double lon, struct keyval *tags) {
    mid->nodes_set(id, lat, lon, tags);
    return out->node_add(id, lat, lon, tags);
}

int osmdata_t::way_add(osmid_t id, osmid_t *nodes, int node_count, struct keyval *tags) {
    return out->way_add(id, nodes, node_count, tags);
}

int osmdata_t::relation_add(osmid_t id, struct member *members, int member_count, struct keyval *tags) {
    return out-> relation_add(id, members, member_count, tags);
}

int osmdata_t::node_modify(osmid_t id, double lat, double lon, struct keyval *tags) {
    slim_middle_t *slim = dynamic_cast<slim_middle_t *>(mid);

    slim->nodes_delete(id);
    slim->nodes_set(id, lat, lon, tags);

    int status = out->node_modify(id, lat, lon, tags);

    slim->node_changed(id);

    return status;
}

int osmdata_t::way_modify(osmid_t id, osmid_t *nodes, int node_count, struct keyval *tags) {
    return out->way_modify(id, nodes, node_count, tags);
}

int osmdata_t::relation_modify(osmid_t id, struct member *members, int member_count, struct keyval *tags) {
    return out->relation_modify(id, members, member_count, tags);
}

int osmdata_t::node_delete(osmid_t id) {
    slim_middle_t *slim = dynamic_cast<slim_middle_t *>(mid);

    int status = out->node_delete(id);

    slim->nodes_delete(id);

    return status;
}

int osmdata_t::way_delete(osmid_t id) {
    return out->way_delete(id);
}

int osmdata_t::relation_delete(osmid_t id) {
    return out->relation_delete(id);
}