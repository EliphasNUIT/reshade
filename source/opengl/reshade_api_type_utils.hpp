/*
 * Copyright (C) 2021 Patrick Mours. All rights reserved.
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

namespace reshade::opengl
{
	struct query_heap_impl
	{
		~query_heap_impl()
		{
			glDeleteQueries(static_cast<GLsizei>(queries.size()), queries.data());
		}

		std::vector<GLuint> queries;
	};

	struct pipeline_layout_impl
	{
		std::vector<GLuint> bindings;
	};

	struct pipeline_compute_impl
	{
		~pipeline_compute_impl()
		{
			glDeleteProgram(program);
		}

		GLuint program;
	};
	struct pipeline_graphics_impl
	{
		~pipeline_graphics_impl()
		{
			glDeleteProgram(program);
			glDeleteVertexArrays(1, &vao);
		}

		GLuint program;
		GLuint vao;

		GLenum prim_mode;
		GLuint patch_vertices;
		GLenum front_face;
		GLenum cull_mode;
		GLenum polygon_mode;

		GLenum blend_eq;
		GLenum blend_eq_alpha;
		GLenum blend_src;
		GLenum blend_dst;
		GLenum blend_src_alpha;
		GLenum blend_dst_alpha;

		GLenum back_stencil_op_fail;
		GLenum back_stencil_op_depth_fail;
		GLenum back_stencil_op_pass;
		GLenum back_stencil_func;
		GLenum front_stencil_op_fail;
		GLenum front_stencil_op_depth_fail;
		GLenum front_stencil_op_pass;
		GLenum front_stencil_func;
		GLuint stencil_read_mask;
		GLuint stencil_write_mask;

		GLboolean blend_enable;
		GLboolean depth_test;
		GLboolean depth_write_mask;
		GLboolean stencil_test;
		GLboolean scissor_test;
		GLboolean multisample;
		GLboolean sample_alpha_to_coverage;
		GLbitfield sample_mask;

		GLuint color_write_mask;
		GLint stencil_reference_value;
	};

	struct descriptor_set_impl
	{
		reshade::api::descriptor_type type;
		std::vector<uint64_t> descriptors;
		std::vector<reshade::api::sampler_with_resource_view> sampler_with_resource_views;
	};

	struct descriptor_set_layout_impl
	{
		reshade::api::descriptor_range range;
	};

	inline api::resource make_resource_handle(GLenum target, GLuint object)
	{
		if (!object)
			return { 0 };
		return { (static_cast<uint64_t>(target) << 40) | object };
	}
	inline api::resource_view make_resource_view_handle(GLenum target, GLuint object, uint8_t extra_bits = 0)
	{
		return { (static_cast<uint64_t>(target) << 40) | (static_cast<uint64_t>(extra_bits) << 32) | object };
	}

	auto convert_format(api::format format) -> GLenum;
	auto convert_format(GLenum internal_format) -> api::format;
	auto convert_attrib_format(api::format format, GLint &size, GLboolean &normalized) -> GLenum;
	auto convert_upload_format(GLenum internal_format, GLenum &type)->GLenum;

	bool is_depth_stencil_format(GLenum internal_format, GLenum usage = GL_DEPTH_STENCIL);

	void convert_memory_heap_to_usage(api::memory_heap heap, GLenum &usage);
	void convert_memory_heap_to_flags(api::memory_heap heap, GLbitfield &flags);
	api::memory_heap convert_memory_heap_from_usage(GLenum usage);
	api::memory_heap convert_memory_heap_from_flags(GLbitfield flags);

	bool check_resource_desc(GLenum target, const api::resource_desc &desc, GLenum &internal_format);
	api::resource_type convert_resource_type(GLenum target);
	api::resource_desc convert_resource_desc(GLenum target, GLsizeiptr buffer_size, api::memory_heap heap);
	api::resource_desc convert_resource_desc(GLenum target, GLsizei levels, GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height = 1, GLsizei depth = 1);

	bool check_resource_view_desc(GLenum target, const api::resource_view_desc &desc, GLenum &internal_format);
	api::resource_view_type convert_resource_view_type(GLenum target);
	api::resource_view_desc convert_resource_view_desc(GLenum target, GLenum internal_format, GLintptr offset, GLsizeiptr size);
	api::resource_view_desc convert_resource_view_desc(GLenum target, GLenum internal_format, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);

	api::subresource_data convert_mapped_subresource(GLenum format, GLenum type, const GLvoid *pixels, GLsizei width, GLsizei height = 1, GLsizei depth = 1);

	GLuint get_index_type_size(GLenum index_type);

	GLenum get_binding_for_target(GLenum target);

	GLenum convert_blend_op(api::blend_op value);
	GLenum convert_blend_factor(api::blend_factor value);
	GLenum convert_fill_mode(api::fill_mode value);
	GLenum convert_cull_mode(api::cull_mode value);
	GLenum convert_compare_op(api::compare_op value);
	GLenum convert_stencil_op(api::stencil_op value);
	GLenum convert_primitive_topology(api::primitive_topology value);
	GLenum convert_query_type(api::query_type type);
	GLenum convert_shader_type(api::shader_stage type);
}
