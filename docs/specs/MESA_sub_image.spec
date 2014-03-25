Name

    MESA_sub_image

Name Strings

    EGL_MESA_sub_image

Contact

    Neil Roberts <neil.s.roberts@intel.com>

Status

    Proposal

Version

    Version 1, March 19, 2014

Number

    EGL Extension #not assigned

Dependencies

    Requires EGL 1.4 or later.  This extension is written against the
    wording of the EGL 1.4 specification.

    EGL_KHR_base_image is required.

Overview

    Allows creating an EGLImage which refers to a sub-region of another
    EGLImage.

IP Status

    Open-source; freely implementable.

New Procedures and Functions

    None.

New Tokens

    Accepted as <target> in eglCreateImageKHR

        EGL_SUB_IMAGE_MESA                      0x3290

    Accepted in the <attrib_list> parameter of eglCreateImageKHR:

        EGL_SUB_IMAGE_X_MESA                    0x3291
        EGL_SUB_IMAGE_Y_MESA                    0x3292
        EGL_SUB_IMAGE_WIDTH_MESA                0x3293
        EGL_SUB_IMAGE_HEIGHT_MESA               0x3294

Additions to the EGL 1.4 Specification:

    To create an EGLImage which refers to a sub-region of another EGLImage,
    call eglCreateImageKHR with the parent image as the EGLClientBuffer,
    EGL_SUB_IMAGE_MESA as the target and NULL as the context. The attributes
    EGL_SUB_IMAGE_X_MESA, EGL_SUB_IMAGE_Y_MESA, EGL_SUB_IMAGE_WIDTH_MESA and
    EGL_SUB_IMAGE_HEIGHT_MESA must be given to specify the region. If the
    specified region is outside the region of the parent image then an
    EGL_BAD_MATCH error is generated. The implementation may also impose
    additional alignment constraints on the region. If these are violated an
    EGL_BAD_ACCESS error will be generated. The contents of the new image are
    shared with the parent image such that any updates to either of them will
    also be reflected in the other one where the regions intersect.

Issues

Revision History

    Version 1, March 19, 2014
        Initial draft (Neil Roberts)
