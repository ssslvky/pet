/*
 * Copyright 2011      Leiden University. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LEIDEN UNIVERSITY ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LEIDEN UNIVERSITY OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as
 * representing official policies, either expressed or implied, of
 * Leiden University.
 */

#include "id.h"

using namespace clang;

/* Create an isl_id that refers to the variable declarator "decl".
 */
__isl_give isl_id *pet_id_from_decl(isl_ctx *ctx, ValueDecl *decl)
{
	return isl_id_alloc(ctx, decl->getName().str().c_str(), decl);
}

/* Create an isl_id that refers to the variable declarator "decl", but
 * has name "name".
 */
__isl_give isl_id *pet_id_from_name_and_decl(isl_ctx *ctx, const char *name,
	ValueDecl *decl)
{
	return isl_id_alloc(ctx, name, decl);
}

/* Extract the ValueDecl that was associated to "id"
 * in pet_id_from_decl.
 */
ValueDecl *pet_id_get_decl(__isl_keep isl_id *id)
{
	return (ValueDecl *) isl_id_get_user(id);
}

/* Construct a pet_expr representing an index expression for an access
 * to the variable represented by "id".
 */
__isl_give pet_expr *pet_id_create_index_expr(__isl_take isl_id *id)
{
	isl_space *space;

	if (!id)
		return NULL;

	space = isl_space_alloc(isl_id_get_ctx(id), 0, 0, 0);
	space = isl_space_set_tuple_id(space, isl_dim_out, id);

	return pet_expr_from_index(isl_multi_pw_aff_zero(space));
}
