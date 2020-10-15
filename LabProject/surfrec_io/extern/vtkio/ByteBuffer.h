#pragma once
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iterator>
#include <iostream>

#include "dynamic_types.h"
#include "endianness.h"
#include "stream_io.h"

namespace bytebuffer
{
	using namespace dynamic_types;
	using namespace endianness;

	// Declarations =====================================================================================
	class ByteBuffer
	{
	protected:
		DataType type = DataType::Undefined;
		ByteOrder byte_order = ByteOrder::Native;
		std::vector<char> data;

	public:
		ByteBuffer() {};
		~ByteBuffer() {};

		// Readers
		template<class InputIterator>
		void setFromIterator(InputIterator begin, InputIterator end, const ByteOrder byte_order = ByteOrder::Native);
		template<class NestedIterator>
		void setFromNestedIterator(NestedIterator begin, NestedIterator end, const size_t n_items, const ByteOrder byte_order = ByteOrder::Native);
		void setFromBinaryStream(std::ifstream& input, const DataType data_type, const size_t n_bytes, const ByteOrder byte_order = ByteOrder::Native);
		void setFromASCIIStream(std::ifstream& input, const DataType data_type, const size_t n_items, const char sep);

		// Writers
		void toStreamBinary(std::ofstream& output, const ByteOrder byte_order = ByteOrder::Native);
		void toStreamASCII(std::ofstream& output, const char sep = ' ');

		// Important functionalities
		void swap();
		void swap(const ByteOrder byte_order);
		template<typename T>
		void castInplace();
		template<typename T>
		ByteBuffer castCopy();

		// Other functions
		DataType getDataType();
		ByteOrder getByteOrder();
		template<typename T>
		T* getDataPtr();
		template <class InputIterator>
		void getDataCopy(InputIterator begin, InputIterator end, const ByteOrder byte_order = ByteOrder::Native);
		template <class NestedIterator>
		void getDataCopyNestedIterator(NestedIterator begin, NestedIterator end, const ByteOrder byte_order = ByteOrder::Native);
		char* getPtrToData();
		size_t getNumberOfBytes();
		size_t getNumberOfItems();
		template<typename T>
		bool isType();
		bool isType(DataType data_type);
		template<typename T>
		void throwIfNotType();
		void clear();

	private:
		void setByteOrder(const ByteOrder byte_order);
		void setDataType(const DataType data_type);
	};



	// Definitions =====================================================================================
	inline void ByteBuffer::setFromBinaryStream(std::ifstream& input, const DataType data_type, const size_t n_bytes, const ByteOrder byte_order)
	{
		this->setDataType(data_type);
		this->setByteOrder(byte_order);
		this->data.clear();
		this->data.resize(n_bytes);
		input.read(this->data.data(), n_bytes);
	}
	inline void ByteBuffer::setFromASCIIStream(std::ifstream& input, const DataType data_type, const size_t n_items, const char sep)
	{
		this->setDataType(data_type);
		this->setByteOrder(ByteOrder::Native);
		this->data.clear();
		const size_t n_bytes = n_items * getDataTypeSize(data_type);
		this->data.resize(n_bytes);
		switch (this->type)
		{
        case DataType::Int16: memcpy(this->data.data(), stream_io::readNumbersASCII<int16_t>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Int32: memcpy(this->data.data(), stream_io::readNumbersASCII<int32_t>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Int64: memcpy(this->data.data(), stream_io::readNumbersASCII<int64_t>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Uint16: memcpy(this->data.data(), stream_io::readNumbersASCII<uint16_t>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Uint32: memcpy(this->data.data(), stream_io::readNumbersASCII<uint32_t>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Uint64: memcpy(this->data.data(), stream_io::readNumbersASCII<uint64_t>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Float32: memcpy(this->data.data(), stream_io::readNumbersASCII<float>(input, n_items, sep).data(), n_bytes); break;
        case DataType::Float64: memcpy(this->data.data(), stream_io::readNumbersASCII<double>(input, n_items, sep).data(), n_bytes); break;
		default:
			throw std::invalid_argument("Invalid cast type used.");
			break;
		}
	}
	inline void ByteBuffer::toStreamBinary(std::ofstream& output, const ByteOrder byte_order)
	{
		this->swap(byte_order);
		output.write(this->data.data(), this->data.size());
	}
	inline void ByteBuffer::toStreamASCII(std::ofstream& output, const char sep)
	{
		const size_t n_elements = this->getNumberOfItems();
		this->swap(ByteOrder::Native);
		switch (this->type)
		{
		case DataType::Int16: { int16_t* begin = this->getDataPtr<int16_t>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Int32: { int32_t* begin = this->getDataPtr<int32_t>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Int64: { int64_t* begin = this->getDataPtr<int64_t>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Uint16: { uint16_t* begin = this->getDataPtr<uint16_t>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Uint32: { uint32_t* begin = this->getDataPtr<uint32_t>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Uint64: { uint64_t* begin = this->getDataPtr<uint64_t>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Float32: { float* begin = this->getDataPtr<float>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		case DataType::Float64: { double* begin = this->getDataPtr<double>(); stream_io::writeNumbersASCII(output, begin, begin + n_elements); } break;
		default:
			throw std::invalid_argument("Invalid cast type used.");
			break;
		}
	}
	inline void bytebuffer::ByteBuffer::swap()
	{
		if (byte_order == ByteOrder::Native) {
			this->byte_order = getNativeEndianness();
		}
		this->byte_order = (this->byte_order == ByteOrder::Big) ? ByteOrder::Little : ByteOrder::Big;
		
		const size_t n_bytes_per_element = getDataTypeSize(this->type);
		switch (n_bytes_per_element) {
		case 1: break;
		case 2: swapByteArrayInplace<1>(this->data); break;
		case 4: swapByteArrayInplace<4>(this->data); break;
		case 8: swapByteArrayInplace<8>(this->data); break;
		default:
			throw std::invalid_argument("Cannot swap this n bytes per element: " + std::to_string(n_bytes_per_element));
			break;
		}
	}
	inline void ByteBuffer::swap(const ByteOrder byte_order)
	{
		if (!sameEndianness(this->byte_order, byte_order)) {
			this->swap();
		}
	}
	inline size_t ByteBuffer::getNumberOfBytes()
	{
		return this->data.size();
	}
	inline size_t bytebuffer::ByteBuffer::getNumberOfItems()
	{
		return this->data.size() / getDataTypeSize(this->type);
	}
	inline DataType ByteBuffer::getDataType()
	{
		return this->type;
	}
	inline ByteOrder ByteBuffer::getByteOrder()
	{
		return this->byte_order;
	}
	inline char* ByteBuffer::getPtrToData()
	{
		return this->data.data();
	}
	inline void ByteBuffer::setByteOrder(const ByteOrder byte_order)
	{
		if (byte_order == ByteOrder::Native) {
			this->byte_order = getNativeEndianness();
		}
		else {
			this->byte_order = byte_order;
		}
	}
	inline void ByteBuffer::setDataType(const DataType data_type)
	{
		if (data_type == DataType::Undefined) {
			throw std::invalid_argument("Invalid cast data type.");
		}
		else {
			this->type = data_type;
		}
	}
	template<class NestedIterator>
	inline void ByteBuffer::setFromNestedIterator(NestedIterator begin, NestedIterator end, const size_t n_items, const ByteOrder byte_order)
	{
		// Checks that it is a 2 level deep container with supported numeric primitive at the bottom
		using T = typename Nested2Iterator<NestedIterator>::nested_value_type;
		isNumberTypeSupported<T>();

		this->setByteOrder(byte_order);
		this->setDataType(dynamic_types::getDataEnumType<T>());
		this->data.clear();
		this->data.resize(n_items * sizeof(T));

		T* casted_buffer = reinterpret_cast<T*>(this->data.data());
		for (auto outer_it = begin; outer_it != end; outer_it++) {
			for (auto inner_it = outer_it->begin(); inner_it != outer_it->end(); inner_it++) {
				*casted_buffer = T(*inner_it);
				casted_buffer++;
			}
		}
	}
	template<class InputIterator>
	inline void ByteBuffer::setFromIterator(InputIterator begin, InputIterator end, const ByteOrder byte_order)
	{
		using T = typename std::iterator_traits<InputIterator>::value_type;
		throwIfNumberTypeNotSupported<T>();

		this->setByteOrder(byte_order);
		this->setDataType(dynamic_types::getDataEnumType<T>());
		const auto n_items = std::distance(begin, end);
		this->data.clear();
		this->data.resize(n_items * sizeof(T));

		T* casted_buffer = reinterpret_cast<T*>(this->data.data());
		for (auto it = begin; it != end; it++) {
			*casted_buffer = T(*it);
			casted_buffer++;
		}
	}
	template<class InputIterator>
	inline void ByteBuffer::getDataCopy(InputIterator begin, InputIterator end, const ByteOrder byte_order)
	{
		using T = typename std::iterator_traits<InputIterator>::value_type;
		this->throwIfNotType<T>();
		const auto n = (size_t)std::distance(begin, end);
		if (n < this->getNumberOfItems()) {
			throw std::invalid_argument("Destination storage is too small to copy the buffer data.");
		}
		this->swap(byte_order);

		T* casted_buffer = reinterpret_cast<T*>(this->data.data());
		for (auto it = begin; it != end; it++) {
			(*it) = *casted_buffer;
			casted_buffer++;
		}
	}
	template<class NestedIterator>
	inline void ByteBuffer::getDataCopyNestedIterator(NestedIterator begin, NestedIterator end, const ByteOrder byte_order)
	{
		using T = typename Nested2Iterator<NestedIterator>::nested_value_type;
		this->throwIfNotType<T>();

		this->swap(byte_order);
		T* buffer_it = this->getDataPtr<T>();
		T* buffer_end = buffer_it + this->getNumberOfItems();
		for (auto outer_it = begin; outer_it != end; outer_it++) {
			for (auto inner_it = outer_it->begin(); inner_it != outer_it->end(); inner_it++) {
				*inner_it = *buffer_it;
				if (buffer_it == buffer_end) { throw std::invalid_argument("Destination storage is too small to copy the buffer data."); }
				buffer_it++;
			}
		}
	}
	template<typename T>
	inline bool ByteBuffer::isType()
	{
		return dynamic_types::getDataEnumType<T>() == this->type;
	}
	inline bool ByteBuffer::isType(DataType data_type)
	{
		return this->type == data_type;
	}
	inline void ByteBuffer::clear()
	{
		DataType type = DataType::Undefined;
		ByteOrder byte_order = ByteOrder::Native;
		this->data.clear();
	}
	template<typename T>
	inline void ByteBuffer::throwIfNotType()
	{
		throwIfNumberTypeNotSupported<T>();
		if (!this->isType<T>()) {
			throw std::invalid_argument("Buffer of type " + dynamic_types::getDataTypeString(this->type) + " is not of type " + dynamic_types::getDataTypeString<T>());
		}
	}
	template<typename T>
	inline void ByteBuffer::castInplace()
	{
		throwIfNumberTypeNotSupported<T>();
		if (this->isType<T>()) {
			return;
		}
		else {
			this->swap(ByteOrder::Native);
			switch (this->type)
			{
			case DataType::Int16: castBytesInPlace<int16_t, T>(this->data); break;
			case DataType::Int32: castBytesInPlace<int32_t, T>(this->data); break;
			case DataType::Int64: castBytesInPlace<int64_t, T>(this->data); break;
			case DataType::Uint16: castBytesInPlace<uint16_t, T>(this->data); break;
			case DataType::Uint32: castBytesInPlace<uint32_t, T>(this->data); break;
			case DataType::Uint64: castBytesInPlace<uint64_t, T>(this->data); break;
			case DataType::Float32: castBytesInPlace<float, T>(this->data); break;
			case DataType::Float64: castBytesInPlace<double, T>(this->data); break;
			default:
				throw std::invalid_argument("Invalid cast type used.");
				break;
			}
			this->setDataType(dynamic_types::getDataEnumType<T>());
		}
	}
	template<typename T>
	inline ByteBuffer ByteBuffer::castCopy()
	{
		ByteBuffer copy;
		copy.castInplace<T>();
		return copy;
	}
	template<typename T>
	inline T* ByteBuffer::getDataPtr()
	{
		this->throwIfNotType<T>();
		return reinterpret_cast<T*>(this->data.data());
	}
}
