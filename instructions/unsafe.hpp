#pragma once

#include "../mizu/opcode.hpp"
#include <fp/pointer.h>

namespace mizu::unsafe {
	inline namespace instructions { extern "C" {

		// out = pointer, a = size in bytes
		void* allocate(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			size_t n = registers[pc->a];
			registers[pc->out] = (size_t)malloc(n);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::allocate);

		// a = pointer to free, b = value to overwrite a with (default zero)
		void* free_allocated(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			void* p = (void*)registers[pc->a];
			free(p);
			registers[pc->a] = registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::free_allocated);


		// out = pointer, a = type size in bytes, b = count
		void* allocate_fat_pointer(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			size_t size = registers[pc->a];
			size_t n = registers[pc->b];
			auto dbg = registers[pc->out] = (size_t)__fp_malloc(size, n);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::allocate_fat_pointer);

		// a = pointer to free, b = value to overwrite a with (default zero)
		void* free_fat_pointer(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			void* p = (void*)registers[pc->a];
			fp_free(p);
			registers[pc->a] = registers[pc->b];
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::free_fat_pointer);

		// out = pointer, a = stack offset (signed)
		void* pointer_to_stack(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto offset = (int64_t&)registers[pc->a];
			auto dbg = registers[pc->out] = (size_t)(sp + offset);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::pointer_to_stack);

		// out = pointer, a = stack offset (signed)
		void* pointer_to_stack_bottom(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto offset = (int64_t&)registers[pc->a];
			auto dbg = registers[pc->out] = (size_t)((uint8_t*)(registers + memory_size) - offset);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::pointer_to_stack);

		// out = pointer, a = register
		void* pointer_to_register(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			auto dbg = registers[pc->out] = (size_t)(registers + pc->a);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::pointer_to_register);

		// out = destination pointer, a = source pointer, b = size in bytes
		void* copy_memory(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			size_t n = registers[pc->b];
			auto src = (void*)registers[pc->a];
			auto dest = (void*)registers[pc->out];
			std::memcpy(dest, src, n);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::copy_memory);

		// out = destination pointer, a = source pointer, b = size in bytes
		void* copy_memory_immediate(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			size_t n = pc->b;
			auto src = (void*)registers[pc->a];
			auto dest = (void*)registers[pc->out];
			std::memcpy(dest, src, n);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::copy_memory_immediate);

		// out = destination pointer, a = value, b = size in bytes
		void* set_memory(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			size_t n = registers[pc->b];
			auto src = (uint8_t)registers[pc->a];
			auto dest = (void*)registers[pc->out];
			std::memset(dest, src, n);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::copy_memory);

		// out = destination pointer, a = value, b = size in bytes
		void* set_memory_immediate(opcode* pc, uint64_t* registers, uint8_t* stack_boundary, uint8_t* sp)
#ifdef MIZU_IMPLEMENTATION
		{
			size_t n = pc->b;
			auto src = (uint8_t)registers[pc->a];
			auto dest = (void*)registers[pc->out];
			std::memset(dest, src, n);
			MIZU_NEXT();
		}
#else
		;
#endif
		MIZU_REGISTER_INSTRUCTION(unsafe::copy_memory_immediate);
	}}
}