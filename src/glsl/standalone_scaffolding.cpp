/*
 * Copyright © 2011 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/* This file declares stripped-down versions of functions that
 * normally exist outside of the glsl folder, so that they can be used
 * when running the GLSL compiler standalone (for unit testing or
 * compiling builtins).
 */

#include "standalone_scaffolding.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "util/ralloc.h"
#include "util/strtod.h"

void
_mesa_warning(struct gl_context *ctx, const char *fmt, ...)
{
    va_list vargs;
    (void) ctx;

    va_start(vargs, fmt);

    /* This output is not thread-safe, but that's good enough for the
     * standalone compiler.
     */
    fprintf(stderr, "Mesa warning: ");
    vfprintf(stderr, fmt, vargs);
    fprintf(stderr, "\n");

    va_end(vargs);
}

void
_mesa_reference_shader(struct gl_context *ctx, struct gl_shader **ptr,
                       struct gl_shader *sh)
{
   (void) ctx;
   *ptr = sh;
}

void
_mesa_shader_debug(struct gl_context *, GLenum, GLuint *,
                   const char *, int)
{
}

struct gl_shader *
_mesa_new_shader(struct gl_context *ctx, GLuint name, GLenum type)
{
   struct gl_shader *shader;

   (void) ctx;

   assert(type == GL_FRAGMENT_SHADER || type == GL_VERTEX_SHADER);
   shader = rzalloc(NULL, struct gl_shader);
   if (shader) {
      shader->Type = type;
      shader->Stage = _mesa_shader_enum_to_shader_stage(type);
      shader->Name = name;
      shader->RefCount = 1;
   }
   return shader;
}

void
_mesa_delete_shader(struct gl_context *ctx, struct gl_shader *sh)
{
   free((void *)sh->Source);
   free(sh->Label);
   ralloc_free(sh);
}

void
_mesa_clear_shader_program_data(struct gl_shader_program *shProg)
{
   unsigned i;

   shProg->NumUniformStorage = 0;
   shProg->UniformStorage = NULL;
   shProg->NumUniformRemapTable = 0;
   shProg->UniformRemapTable = NULL;
   shProg->UniformHash = NULL;

   ralloc_free(shProg->InfoLog);
   shProg->InfoLog = ralloc_strdup(shProg, "");

   ralloc_free(shProg->BufferInterfaceBlocks);
   shProg->BufferInterfaceBlocks = NULL;
   shProg->NumBufferInterfaceBlocks = 0;

   ralloc_free(shProg->UniformBlocks);
   shProg->UniformBlocks = NULL;
   shProg->NumUniformBlocks = 0;

   ralloc_free(shProg->ShaderStorageBlocks);
   shProg->ShaderStorageBlocks = NULL;
   shProg->NumShaderStorageBlocks = 0;

   for (i = 0; i < MESA_SHADER_STAGES; i++) {
      ralloc_free(shProg->UniformBlockStageIndex[i]);
      shProg->UniformBlockStageIndex[i] = NULL;
   }

   ralloc_free(shProg->AtomicBuffers);
   shProg->AtomicBuffers = NULL;
   shProg->NumAtomicBuffers = 0;
}

void initialize_context_to_defaults(struct gl_context *ctx, gl_api api)
{
   memset(ctx, 0, sizeof(*ctx));

   ctx->API = api;

   ctx->Extensions.dummy_false = false;
   ctx->Extensions.dummy_true = true;
   ctx->Extensions.ARB_compute_shader = true;
   ctx->Extensions.ARB_conservative_depth = true;
   ctx->Extensions.ARB_draw_instanced = true;
   ctx->Extensions.ARB_ES2_compatibility = true;
   ctx->Extensions.ARB_ES3_compatibility = true;
   ctx->Extensions.ARB_explicit_attrib_location = true;
   ctx->Extensions.ARB_fragment_coord_conventions = true;
   ctx->Extensions.ARB_fragment_layer_viewport = true;
   ctx->Extensions.ARB_gpu_shader5 = true;
   ctx->Extensions.ARB_gpu_shader_fp64 = true;
   ctx->Extensions.ARB_sample_shading = true;
   ctx->Extensions.ARB_shader_bit_encoding = true;
   ctx->Extensions.ARB_shader_stencil_export = true;
   ctx->Extensions.ARB_shader_subroutine = true;
   ctx->Extensions.ARB_shader_texture_lod = true;
   ctx->Extensions.ARB_shading_language_420pack = true;
   ctx->Extensions.ARB_shading_language_packing = true;
   ctx->Extensions.ARB_tessellation_shader = true;
   ctx->Extensions.ARB_texture_cube_map_array = true;
   ctx->Extensions.ARB_texture_gather = true;
   ctx->Extensions.ARB_texture_multisample = true;
   ctx->Extensions.ARB_texture_query_levels = true;
   ctx->Extensions.ARB_texture_query_lod = true;
   ctx->Extensions.ARB_uniform_buffer_object = true;
   ctx->Extensions.ARB_viewport_array = true;

   ctx->Extensions.OES_EGL_image_external = true;
   ctx->Extensions.OES_standard_derivatives = true;

   ctx->Extensions.EXT_shader_integer_mix = true;
   ctx->Extensions.EXT_texture3D = true;
   ctx->Extensions.EXT_texture_array = true;

   ctx->Extensions.NV_texture_rectangle = true;

   ctx->Const.GLSLVersion = 120;

   /* 1.20 minimums. */
   ctx->Const.MaxLights = 8;
   ctx->Const.MaxClipPlanes = 6;
   ctx->Const.MaxTextureUnits = 2;
   ctx->Const.MaxTextureCoordUnits = 2;
   ctx->Const.Program[MESA_SHADER_VERTEX].MaxAttribs = 16;

   ctx->Const.Program[MESA_SHADER_VERTEX].MaxUniformComponents = 512;
   ctx->Const.Program[MESA_SHADER_VERTEX].MaxOutputComponents = 32;
   ctx->Const.MaxVarying = 8; /* == gl_MaxVaryingFloats / 4 */
   ctx->Const.Program[MESA_SHADER_VERTEX].MaxTextureImageUnits = 0;
   ctx->Const.MaxCombinedTextureImageUnits = 2;
   ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxTextureImageUnits = 2;
   ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxUniformComponents = 64;
   ctx->Const.Program[MESA_SHADER_FRAGMENT].MaxInputComponents = 32;

   ctx->Const.MaxDrawBuffers = 1;
   ctx->Const.MaxComputeWorkGroupCount[0] = 65535;
   ctx->Const.MaxComputeWorkGroupCount[1] = 65535;
   ctx->Const.MaxComputeWorkGroupCount[2] = 65535;
   ctx->Const.MaxComputeWorkGroupSize[0] = 1024;
   ctx->Const.MaxComputeWorkGroupSize[1] = 1024;
   ctx->Const.MaxComputeWorkGroupSize[2] = 64;
   ctx->Const.MaxComputeWorkGroupInvocations = 1024;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxTextureImageUnits = 16;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxUniformComponents = 1024;
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxInputComponents = 0; /* not used */
   ctx->Const.Program[MESA_SHADER_COMPUTE].MaxOutputComponents = 0; /* not used */

   /* Set up default shader compiler options. */
   struct gl_shader_compiler_options options;
   memset(&options, 0, sizeof(options));
   options.MaxUnrollIterations = 32;
   options.MaxIfDepth = UINT_MAX;

   for (int sh = 0; sh < MESA_SHADER_STAGES; ++sh)
      memcpy(&ctx->Const.ShaderCompilerOptions[sh], &options, sizeof(options));

   _mesa_locale_init();
}
