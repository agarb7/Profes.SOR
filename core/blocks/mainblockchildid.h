#ifndef MAINBLOCKCHILDID_H
#define MAINBLOCKCHILDID_H

namespace Core {

struct MainBlockChildId {
    enum {
        Map,
        GeneralParameters,
        SupplierParameters,
        FixedParameters,
        KeyEvents,
        LinkParameters,
        DataPoints,
        NetTekOtdr10,
        Checksum,
        BlockEnumSize
    };
};

} // namespace Core

#endif // MAINBLOCKCHILDID_H
