#pragma once
#include <cstdint>

namespace adze {
	enum class ShaderDataType {
		Node = 0,
		float1,
		float2,
		float3,
		float4,
		matrix3,
		matrix4,
		integer1,
		integer2, 
		integer3,
		integer4,
		boolean
	};

	static uint32_t getShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::float1: return 4;
			case ShaderDataType::float2: return 4 * 2;
			case ShaderDataType::float3: return 4 * 3;
			case ShaderDataType::float4: return 4 * 4;
			case ShaderDataType::matrix3: return 3 * 3 * 3;
			case ShaderDataType::matrix4: return 4 * 4 * 4;
			case ShaderDataType::integer1: return 4;
			case ShaderDataType::integer2: return 4 * 2;
			case ShaderDataType::integer3: return 4 * 3;
			case ShaderDataType::integer4: return 4 * 4;
			case ShaderDataType::boolean: return 1;
		}
		
		ADZE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string name;
		uint32_t offset;
		uint32_t size;
		ShaderDataType type;
		bool normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : name(name), type(type), size(getShaderDataTypeSize(type)), offset(0), normalized(normalized) {

		}

		uint32_t getComponentCount() const {
			switch (type) {
				case ShaderDataType::float1: return 1;
				case ShaderDataType::float2: return 2;
				case ShaderDataType::float3: return 3;
				case ShaderDataType::float4: return 4;
				case ShaderDataType::matrix3: return 3 * 3;
				case ShaderDataType::matrix4: return 4 * 4;
				case ShaderDataType::integer1: return 4;
				case ShaderDataType::integer2: return 2;
				case ShaderDataType::integer3: return 3;
				case ShaderDataType::integer4: return 4;
				case ShaderDataType::boolean: return 1;
			}
			
			ADZE_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& list) : elements(list) {
			calculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& getElements() const { return elements; }
		inline const uint32_t getStride() const { return stride; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::reverse_iterator rbegin() { return elements.rbegin(); }
		std::vector<BufferElement>::reverse_iterator rend() { return elements.rend(); }

		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
		std::vector<BufferElement>::const_reverse_iterator rbegin() const { return elements.rbegin(); }
		std::vector<BufferElement>::const_reverse_iterator rend() const { return elements.rend(); }
	private:
		void calculateOffsetsAndStride() {
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements) {
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}

		std::vector<BufferElement> elements;
		uint32_t stride;

	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* create(float* vertices, uint32_t size);

	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static IndexBuffer* create(uint32_t* vertices, uint32_t count);
	};
}
