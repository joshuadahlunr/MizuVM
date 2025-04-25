#pragma once

#include "f32.hpp"

namespace mizu {
	inline namespace instructions { extern "C" {

		void* convert_f32_to_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			float_register<std::float64_t>(registers, pc->out) = float_register<std::float32_t>(registers, pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_f32_to_f64);

		void* convert_f64_to_f32(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			float_register<std::float32_t>(registers, pc->out) = float_register<std::float64_t>(registers, pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_f64_to_f64);

// 		void* stack_load_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
// #ifdef MIZU_IMPLEMENTATION
// 		{
// 			float_register<std::float64_t>(registers, pc->out) = *(std::float64_t*)(sp + registers[pc->a]);
// 			MIZU_NEXT();
// 		}
// #else
// 		;
// #endif
// 		MIZU_REGISTER_INSTRUCTION(stack_load_f64);

// 		void* stack_store_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
// #ifdef MIZU_IMPLEMENTATION
// 		{
// 			float_register<std::float64_t>(registers, pc->out) = *(std::float64_t*)(sp + registers[pc->a]) = (std::float64_t&)registers[pc->b];
// 			MIZU_NEXT();
// 		}
// #else
// 		;
// #endif
// 		MIZU_REGISTER_INSTRUCTION(stack_store_f64);

		void* convert_to_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			float_register<std::float64_t>(registers, pc->out) = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_to_f64);

		void* convert_signed_to_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			float_register<std::float64_t>(registers, pc->out) = (int64_t&)registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_signed_to_f64);

		void* convert_from_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float64_t>(registers, pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_from_f64);

		void* convert_signed_from_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = (int64_t&)registers[pc->out] = float_register<std::float64_t>(registers, pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(convert_signed_from_f64);

		void* add_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = float_register<std::float64_t>(registers, pc->a) + float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(add_f64);

		void* subtract_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = float_register<std::float64_t>(registers, pc->a) - float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(subtract_f64);

		void* multiply_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = float_register<std::float64_t>(registers, pc->a) * float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(multiply_f64);

		void* divide_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = float_register<std::float64_t>(registers, pc->a) / float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(divide_f64);

		void* max_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = std::max(float_register<std::float64_t>(registers, pc->a), float_register<std::float64_t>(registers, pc->b));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(max_f64);

		void* min_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION 
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = std::min(float_register<std::float64_t>(registers, pc->a), float_register<std::float64_t>(registers, pc->b));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(min_f64);

		void* sqrt_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = float_register<std::float64_t>(registers, pc->out) = std::sqrt(float_register<std::float64_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(sqrt_f64);


		void* set_if_equal_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float64_t>(registers, pc->a) == float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_equal_f64);

		void* set_if_not_equal_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float64_t>(registers, pc->a) != float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_not_equal_f64);

		void* set_if_less_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float64_t>(registers, pc->a) < float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_less_f64);

		void* set_if_greater_equal_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = float_register<std::float64_t>(registers, pc->a) >= float_register<std::float64_t>(registers, pc->b);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_greater_equal_f64);


		void* set_if_negative_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = std::signbit(float_register<std::float64_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_negative_f64);

		void* set_if_positive_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = !std::signbit(float_register<std::float64_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_positive_f64);

		void* set_if_infinity_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = std::isinf(float_register<std::float64_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_infinity_f64);

		void* set_if_nan_f64(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp) 
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = std::isnan(float_register<std::float64_t>(registers, pc->a));
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(set_if_nan_f64);
	}}
}