#pragma once

// #include <cstdint>
// #include <cstdio>
// #include <string_view>
#include "opcode.hpp"

#include <fp/string.h>

namespace mizu {

	constexpr uint32_t label2int(const fp_string_view label) {
		size_t length = fp_string_view_length(label);
		if(length > sizeof(uint32_t)) return *fp_view_data(uint32_t, label);

		uint32_t out = 0;
		for(size_t i = 0; i < fp_string_view_length(label); ++i)
			out |= fp_view_data(char, label)[i] << (i * 8);
		return out;
	}
	constexpr uint32_t label2int(const fp_string label) { return label2int(fp_string_to_view_const(label)); }

	inline namespace operations { extern "C" {
		void* label(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			MIZU_NEXT();
		}
#else
		;
#endif

		void* find_label(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto needle = *(uint32_t*)&pc->a;
			registers[pc->out] = 0;
			for(size_t i = 0; i < memory_size; ++i)
				if(auto l = pc + i; l->op == label && *(uint32_t*)&l->a == needle) {
					registers[pc->out] = (uint64_t)l;
					break;
				}
			if(registers[pc->out] == 0)
				for(size_t i = 0; i < memory_size; ++i)
					if(auto l = pc - i; l->op == label && *(uint32_t*)&l->a == needle) {
						registers[pc->out] = (uint64_t)l;
						break;
					}
			opcode* dbg = (opcode*)registers[pc->out];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* halt(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
	#ifdef MIZU_NO_HARDWARE_THREADS
			mizu::coroutine::get_current_context().program_counter = nullptr; // Mark the coroutine context as done!
	#endif
			return nullptr;
		}
#else // MIZU_IMPLEMENTATION
		;
#endif

		void* debug_print(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			printf("u64 = %lu, i64 = %ld, f64 = %f, f32 = %f\n", registers[pc->a], (int64_t&)registers[pc->a], (double&)registers[pc->a], (float&)registers[pc->a]);
			fflush(stdout); // Make sure buffer is flushed!
			MIZU_NEXT();
		}
#else
		;
#endif

		void* debug_print_binary(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			constexpr static auto print_binary = [](void* ptr){ // From: https://stackoverflow.com/a/3974138
				uint8_t* b = (uint8_t*)ptr;

				printf("binary = ");
				for(int8_t i = sizeof(uint64_t)-1; i >= 0; --i)
					for(int8_t j = 7; j >= 0; --j) {
						uint8_t byte = (b[i] >> j) & 1;
						printf("%u", byte);
					}
			};

			print_binary(&registers[pc->a]);
			printf(", ");
			return debug_print(pc, registers, stack, sp);
		}
#else
		;
#endif

		void* load_immediate(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint32_t*)&pc->a;
			MIZU_NEXT();
		}
#else
		;
#endif

		void* load_upper_immediate(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] |= uint64_t(*(uint32_t*)&pc->a) << 32;
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_u64(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(uint64_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_i64(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(int64_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_u32(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(uint32_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_i32(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(int32_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_u16(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(uint16_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_i16(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(int16_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_u8(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(uint8_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* convert_to_i8(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			*(int8_t*)&registers[pc->out] = registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_u64(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint64_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_i64(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int64_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_u64(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint64_t*)(sp + registers[pc->a]) = *(uint64_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_i64(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint64_t*)(sp + registers[pc->a]) = *(uint64_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_u32(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint32_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_i32(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int32_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_u32(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint32_t*)(sp + registers[pc->a]) = *(uint32_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_i32(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint32_t*)(sp + registers[pc->a]) = *(uint32_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_u16(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint16_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_i16(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int16_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_u16(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint16_t*)(sp + registers[pc->a]) = *(uint16_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_i16(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint16_t*)(sp + registers[pc->a]) = *(uint16_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_u8(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint8_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_load_i8(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int8_t*)(sp + registers[pc->a]);
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_u8(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint8_t*)(sp + registers[pc->a]) = *(uint8_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_store_i8(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(uint8_t*)(sp + registers[pc->a]) = *(uint8_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_push(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			sp -= registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_push_immediate(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto& size = *(uint32_t*)&pc->a;
			sp -= size;
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_pop(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			sp += registers[pc->a];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* stack_pop_immediate(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto& size = *(uint32_t*)&pc->a;
			sp += size;
			MIZU_NEXT();
		}
#else
		;
#endif

		// Interpret register as signed
		void* jump_relative(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto a = registers[pc->a];
			registers[pc->out] = (uint64_t)(pc + 1);
			pc += *(int64_t*)&a - 1;
			MIZU_NEXT();
		}
#else
		;
#endif

		// Interpret arguments as signed
		void* jump_relative_immediate(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = (uint64_t)(pc + 1);
			pc += *(int32_t*)&pc->a - 1;
			MIZU_NEXT();
		}
#else
		;
#endif

		void* jump_to(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = (uint64_t)(pc + 1);
			pc = (opcode*)registers[pc->a] - 1;
			MIZU_NEXT();
		}
#else
		;
#endif

		// Interpret register as signed
		void* branch_relative(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = (uint64_t)(pc + 1);
			if(registers[pc->a])
				pc += *(int64_t*)&registers[pc->b] - 1;
			MIZU_NEXT();
		}
#else
		;
#endif

		// Interpret arguments as signed
		void* branch_relative_immediate(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = (uint64_t)(pc + 1);
			if(registers[pc->a])
				pc += *(int16_t*)&pc->b - 1;
			MIZU_NEXT();
		}
#else
		;
#endif

		void* branch_to(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = (uint64_t)(pc + 1);
			if(registers[pc->a])
				pc = (opcode*)registers[pc->b] - 1;
			MIZU_NEXT();
		}
#else
		;
#endif

		void* set_if_equal(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] == registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* set_if_not_equal(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] != registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* set_if_less(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] < registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* set_if_less_signed(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int64_t*)&registers[pc->a] < *(int64_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* set_if_greater_equal(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] >= registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* set_if_greater_equal_signed(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int64_t*)&registers[pc->a] >= *(int64_t*)&registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* add(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] + registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* subtract(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] - registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* multiply(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] * registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* divide(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] / registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* modulus(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] % registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* shift_left(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] << registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* shift_right_logical(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] >> registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* shift_right_arithmetic(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = *(int64_t*)&registers[pc->a] >> registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* bitwise_xor(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] ^ registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* bitwise_and(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] & registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif

		void* bitwise_or(opcode* pc, uint64_t* registers, uint8_t* stack, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			registers[pc->out] = registers[pc->a] | registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif
	}}
}