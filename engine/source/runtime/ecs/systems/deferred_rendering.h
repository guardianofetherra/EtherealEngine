#pragma once

#include "../ecs.h"
#include <vector>
#include <memory>
#include <chrono>
#include "../../rendering/program.h"

class Camera;
class RenderView;

namespace runtime
{
	struct LodData
	{
		std::uint32_t current_lod_index = 0;
		std::uint32_t target_lod_index = 0;
		float current_time = 0.0f;
	};

	class DeferredRendering : public core::Subsystem
	{
	public:
		//-----------------------------------------------------------------------------
		//  Name : frameRender (virtual )
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		void frame_render(std::chrono::duration<float> dt);

		//-----------------------------------------------------------------------------
		//  Name : receive ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		void receive(Entity e);

		//-----------------------------------------------------------------------------
		//  Name : initialize ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		bool initialize() override;

		//-----------------------------------------------------------------------------
		//  Name : dispose ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		void dispose() override;


		//-----------------------------------------------------------------------------
		//  Name : scene_pass ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		std::shared_ptr<FrameBuffer> deferred_render_full(
			Camera& camera,
			RenderView& render_view,
			EntityComponentSystem& ecs,
			std::unordered_map<Entity, LodData>& camera_lods,
			std::chrono::duration<float> dt);

		//-----------------------------------------------------------------------------
		//  Name : g_buffer_pass ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		std::shared_ptr<FrameBuffer> g_buffer_pass(
			std::shared_ptr<FrameBuffer> input,
			Camera& camera,
			RenderView& render_view,
			EntityComponentSystem& ecs,
			std::unordered_map<Entity, LodData>& camera_lods, 
			std::chrono::duration<float> dt);

		//-----------------------------------------------------------------------------
		//  Name : lighting_pass ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		std::shared_ptr<FrameBuffer> lighting_pass(
			std::shared_ptr<FrameBuffer> input,
			Camera& camera, 
			RenderView& render_view,
			EntityComponentSystem& ecs,
			std::chrono::duration<float> dt);

		//-----------------------------------------------------------------------------
		//  Name : reflection_probe ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		std::shared_ptr<FrameBuffer> reflection_probe_pass(
			std::shared_ptr<FrameBuffer> input,
			Camera& camera,
			RenderView& render_view,
			EntityComponentSystem& ecs,
			std::chrono::duration<float> dt);

		//-----------------------------------------------------------------------------
		//  Name : atmospherics_pass ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		std::shared_ptr<FrameBuffer> atmospherics_pass(
			std::shared_ptr<FrameBuffer> input,
			Camera& camera,
			RenderView& render_view,
			EntityComponentSystem& ecs,
			std::chrono::duration<float> dt);

		//-----------------------------------------------------------------------------
		//  Name : tonemapping_pass ()
		/// <summary>
		/// 
		/// 
		/// 
		/// </summary>
		//-----------------------------------------------------------------------------
		std::shared_ptr<FrameBuffer> tonemapping_pass(
			std::shared_ptr<FrameBuffer> input,
			Camera& camera,
			RenderView& render_view);
	private:
		std::unordered_map<Entity, std::unordered_map<Entity, LodData>> _lod_data;
		/// Program that is responsible for rendering.
		std::unique_ptr<Program> _directional_light_program;
		/// Program that is responsible for rendering.
		std::unique_ptr<Program> _point_light_program;
		/// Program that is responsible for rendering.
		std::unique_ptr<Program> _spot_light_program;
		/// Program that is responsible for rendering.
		std::unique_ptr<Program> _sphere_ref_probe_program;
		/// Program that is responsible for rendering.
		std::unique_ptr<Program> _gamma_correction_program;
		/// Program that is responsible for rendering.
		std::unique_ptr<Program> _atmospherics_program;
	};

}