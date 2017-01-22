#ifndef MAINBLOCKCHILDID_H
#define MAINBLOCKCHILDID_H

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

#endif // MAINBLOCKCHILDID_H
