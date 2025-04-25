#pragma once

#include "../mizu/opcode.hpp"

#include <cmath>
#include <stdfloat>
#include <concepts>

namespace mizu {
	template<std::floating_point F>
	inline F& float_register(uint64_t* registers, uint16_t index) {
		return (F&)registers[index];
	}

	inline namespace instructions { extern "C" {

// 		void* stack_load_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
// #ifdef MIZU_IMPLEMENTATION
// 		{
// 			float_register<std::float32_t>(registers, pc->out) = *(std::float32_t*)(sp + registers[pc->a]);
// 			MIZU_NEXT();
// 		}
// #else
// 		;
// #endif
// 		MIZU_REGISTER_INSTRUCTION(stack_load_f32);

// 		void* stack_store_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
// #ifdef MIZU_IMPLEMENTATION
// 		{
// 			float_register<std::float32_t>(registers, pc->out) = *(std::float32_t*)(sp + registers[pc->a]) = (std::float32_t&)registers[pc->b];
// 			MIZU_NEXT();
// 		}
// #else
// 		;
// #endif
// 		MIZU_REGISTER_INSTRUCTION(stack_store_f32);

		void* convert_to_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			float_register<std::float32_t>(registers, pc->out) = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_to_f32);

		void* convert_signed_to_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			float_register<std::float32_t>(registers, pc->out) = (int64_t&)registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_signed_to_f32);

		void* convert_from_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float32_t>(registers, pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_from_f32);

		void* convert_signed_from_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = (int64_t&)registers[pc->out] = float_register<std::float32_t>(registers, pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_signed_from_f32);

		void* add_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = float_register<std::float32_t>(registers, pc->a) + float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(add_f32);

		void* subtract_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = float_register<std::float32_t>(registers, pc->a) - float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(subtract_f32);

		void* multiply_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = float_register<std::float32_t>(registers, pc->a) * float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(multiply_f32);

		void* divide_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = float_register<std::float32_t>(registers, pc->a) / float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(divide_f32);

		void* max_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = std::max(float_register<std::float32_t>(registers, pc->a), float_register<std::float32_t>(registers, pc->b));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(max_f32);

		void* min_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION 
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = std::min(float_register<std::float32_t>(registers, pc->a), float_register<std::float32_t>(registers, pc->b));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(min_f32);

		void* sqrt_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float32_t>(registers, pc->out) = std::sqrt(float_register<std::float32_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(sqrt_f32);


		void* set_if_equal_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float32_t>(registers, pc->a) == float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_equal_f32);

		void* set_if_not_equal_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float32_t>(registers, pc->a) != float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_not_equal_f32);

		void* set_if_less_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float32_t>(registers, pc->a) < float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_less_f32);

		void* set_if_greater_equal_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float32_t>(registers, pc->a) >= float_register<std::float32_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_greater_equal_f32);


		void* set_if_negative_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = std::signbit(float_register<std::float32_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_negative_f32);

		void* set_if_positive_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = !std::signbit(float_register<std::float32_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_positive_f32);

		void* set_if_infinity_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = std::isinf(float_register<std::float32_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_infinity_f32);

		void* set_if_nan_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = std::isnan(float_register<std::float32_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_nan_f32);
	}}
}