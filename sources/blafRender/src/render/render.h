// (render\render.h) This file is part of BLAF Render module.
// Licensed under the MIT License. See LICENSE file in the project root for full.

#ifndef BLAFRENDER_RENDER_RENDER_H
#define BLAFRENDER_RENDER_RENDER_H

namespace BLAF
{
	/**	@brief Renderer class. (Interface)
	*
	*	This class is responsible for rendering.
	*/
	class Renderer
	{
	public:
		/** @brief Initialize method.
		*
		*	Initializes renderer.
		*/
		virtual bool Initialize() = 0;

		/** @brief Deinitialize method.
		*
		*	Deinitializes renderer.
		*/
		virtual void Deinitialize() = 0;

		/** @brief Render method.
		*
		*	Render graphics. Calls on every application update.
		*/
		virtual void Render() = 0;

	};
}

#endif