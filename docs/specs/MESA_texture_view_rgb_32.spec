Name

    MESA_texture_view_rgb_32

Name Strings

    GL_MESA_texture_view_rgb_32

Contact

    Neil Roberts, Intel Corporation (neil.s.roberts 'at' intel.com)

Notice

    Copyright (c) 2015 Intel corporation

Status

    Proposal

Version

    Last Modified Date: 14 December 2015
    Revision: 1

Number

    ???

Dependencies

    This extension is written against the OpenGL 4.5 Core profile 
    specification.

    ARB_texture_view or OpenGL 4.3 is required.

Overview

    In unextended GL texture formats are categorized into various view
    classes and it is only possible to make a texture view of a
    texture with a format in the same class. There is a separate class
    for 24-bit formats which have 3 components and a byte per
    component. However in practice in most hardware these are actually
    padded out to 32 bits per pixel with the extra 8 bits left unused.
    Because of this it is trivial for most hardware to allow views to
    be created between the 32- and 24- bit classes. This extension
    enables that.

New Procedures and Functions

    None

New Tokens

    None

Additions to Chapter 8 of the OpenGL 4.5 Specification (Textures and Samplers)

    Modify subsection 8.18 (Texture Views)

    Replace the caption for table 8.22 with the following:

    Table 8.22: Compatible internal formats for TextureView. Formats
    listed in the rows VIEW_CLASS_32_BITS and VIEW_CLASS_24_BITS may
    all be cast to each other, even between the two rows. Formats
    in other rows may be cast to other formats in the same row.

Errors

    None

New State

    None

New Implementation Dependent State

    None

Examples

    TODO

Issues

    None

Revision History

    Rev.    Date    Author    Changes
    ----  --------  --------  -----------------------------------------
      1   14/12/15  nroberts  Initial revision
