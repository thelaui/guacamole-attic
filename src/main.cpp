#include "include/utils/debug.hpp"

#include "include/renderer/MaterialBase.hpp"

int main() {

    {
        MaterialBase* base = new MaterialBase();
        base->add("first", std::shared_ptr<Material>(new Material()));
    }

    MaterialBase* m(MaterialBase::pointer());
    if (m->is_supported("huhu")) DEBUG("huhu is supported");
    else                         DEBUG("huhu not supported");

    if (m->is_supported("first")) DEBUG("first is supported");
    else                         DEBUG("first not supported");

    return 0;
}
