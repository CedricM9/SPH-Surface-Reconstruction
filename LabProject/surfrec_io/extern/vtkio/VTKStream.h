#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <type_traits>
#include <stdexcept>
#include <iostream>

#include "endianness.h"
#include "ByteBuffer.h"
#include "tables.h"

namespace vtkio
{
	using namespace dynamic_types;
	using namespace endianness;

	// Declarations =====================================================================================
	struct VTKData
	{
		vtkio::tables::AttributeType attr_type;
		bytebuffer::ByteBuffer buffer;
	};

	class VTKStream
	{
	/* Fields */
	public:
		// These data is stored as it is writen/read in the VTK file format
		// The user can directly modify these buffers to operate VTKStream without using the provided interface methods
		bytebuffer::ByteBuffer points;
		bytebuffer::ByteBuffer cells;
		bytebuffer::ByteBuffer cell_types;
		std::unordered_map<std::string, VTKData> point_data;
		std::unordered_map<std::string, VTKData> cell_data;
		std::string comments;

	/* Methods */
	public:
		VTKStream() {};
		~VTKStream() {};

		// Setters -----------------------------------------------------------------------
		template<class InputIterator>
		void setPoints(InputIterator begin, InputIterator end, const size_t dim = 3, const ByteOrder byte_order = ByteOrder::Native);
		template<class VecContainer>
		void setPointsNestedIterator(VecContainer begin, VecContainer end, const size_t dim = 3, const ByteOrder byte_order = ByteOrder::Native);

		template<class InputIterator>
		void setCells(InputIterator begin, InputIterator end, const vtkio::tables::CellType cell_type, const ByteOrder byte_order = ByteOrder::Native);
		template<class ElementIterator, class ElementTypeIterator>
		void setCells(ElementIterator cells_begin, ElementIterator cells_end, ElementTypeIterator cell_types_begin, ElementTypeIterator cell_types_end, const ByteOrder byte_order = ByteOrder::Native);
		template<class NestedIterator>
		void setCellsNestedIterator(NestedIterator begin, NestedIterator end, const vtkio::tables::CellType cell_type, const ByteOrder byte_order = ByteOrder::Native);
		template<class ElementNestedIterator, class ElementTypeIterator>
		void setCellsNestedIterator(ElementNestedIterator cells_begin, ElementNestedIterator cells_end, ElementTypeIterator cell_types_begin, ElementTypeIterator cell_types_end, const ByteOrder byte_order = ByteOrder::Native);

		template<class InputIterator>
		void setPointData(const std::string label, InputIterator begin, InputIterator end, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order = ByteOrder::Native);
		template<class VecContainer>
		void setPointDataNestedIterator(const std::string label, VecContainer begin, VecContainer end, const size_t dim, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order = ByteOrder::Native);

		template<class InputIterator>
		void setCellData(const std::string label, InputIterator begin, InputIterator end, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order = ByteOrder::Native);
		template<class VecContainer>
		void setCellDataNestedIterator(const std::string label, VecContainer begin, VecContainer end, const size_t dim, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order = ByteOrder::Native);

		void setComments(const std::string comments);

		// Getters -----------------------------------------------------------------------
		size_t getNumberOfPoints();
		size_t getNumberOfCells();
		std::string getComments();

		template<class OutputIterator>
		void getPoints(OutputIterator begin, OutputIterator end, const size_t dim = 3, const ByteOrder byte_order = ByteOrder::Native);
		template<class OutputVecIterator>
		void getPointsNestedIterator(OutputVecIterator begin, OutputVecIterator end, const size_t dim = 3, const ByteOrder byte_order = ByteOrder::Native);

		template<class OutputIterator>
		void getCells(OutputIterator begin, OutputIterator end);
		template<class OutputNestedIterator>
		void getCellsNestedIterator(OutputNestedIterator begin, OutputNestedIterator end);
		template<class OutputIterator>
		void getCellsTypes(OutputIterator begin, OutputIterator end);

		size_t getPointDataDimensions(const std::string label);
		template<class OutputIterator>
		void getPointData(const std::string label, OutputIterator begin, OutputIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order = ByteOrder::Native);
		template<class OutputVecIterator>
		void getPointDataVecIterator(const std::string label, OutputVecIterator begin, OutputVecIterator end, vtkio::tables::AttributeType &attr_type_out, const ByteOrder byte_order = ByteOrder::Native);

		size_t getCellDataDimensions(const std::string label);
		template<class OutputIterator>
		void getCellData(const std::string label, OutputIterator begin, OutputIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order = ByteOrder::Native);
		template<class OutputVecIterator>
		void getCellDataVecIterator(const std::string label, OutputVecIterator begin, OutputVecIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order = ByteOrder::Native);

		// IO -----------------------------------------------------------------------
		void write(const std::string path, const bool binary = true);
		void read(const std::string path);
		static void write_empty(const std::string path);
		
		// Other functions -----------------------------------------------------------------------
		void check();
		void clear();


	private:
		// Auxiliar methods
		size_t _getDataDimensions(const bool point_data, const std::string label);
		template<class InputIterator>
		void _setData(const bool point_data, const std::string label, InputIterator begin, InputIterator end, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order);
		template<class VecContainer>
		void _setDataNestedIterator(const bool point_data, const std::string label, VecContainer begin, VecContainer end, const size_t dim, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order);
		template<class OutputIterator>
		void _getData(const bool point_data, const std::string label, OutputIterator begin, OutputIterator end, vtkio::tables::AttributeType& attr_type, const ByteOrder byte_order);
		template<class OutputVecIterator>
		void _getDataVecIterator(const bool point_data, const std::string label, OutputVecIterator begin, OutputVecIterator end, vtkio::tables::AttributeType& attr_type, const ByteOrder byte_order);
	};


	// Definitions =====================================================================================
	inline void VTKStream::check()
	{
		if (this->comments.find('\n') != std::string::npos) { throw std::invalid_argument("Comments cannot contain '\n'"); }
		if (this->comments.length() > 256) { throw std::length_error("Comments cannot be larger than 256 characters."); }

		// Points
		if (this->getNumberOfPoints() == 0) { throw std::length_error("Point array is empty."); }
		if (!(this->points.isType<float>() || this->points.isType<double>())) { 
			throw std::length_error("Points must be float or double. Consider using VTKStream.points.castInPlace<double>();"); 
		};
		
		// Cells
		if (this->getNumberOfCells() == 0) { throw std::length_error("Cells array is empty."); }
		if (!this->cells.isType<int32_t>()) {
			throw std::length_error("Cells must be int32_t. Consider using VTKStream.cells.castInPlace<int>();");
		};

		// Data
		auto checkVTKData = [&](const size_t n_entities, std::unordered_map<std::string, VTKData>& data)
		{
			for (auto& key_value : data) {
				std::string label = key_value.first;
				VTKData& vtk_data = key_value.second;
				bytebuffer::ByteBuffer& byte_buffer = vtk_data.buffer;
				const size_t n_data = byte_buffer.getNumberOfItems();
				const size_t dim = n_data / n_entities;
				if (n_data == 0) { throw std::length_error(label + " data array is empty."); }
				if (dim*n_entities != n_data) { throw std::length_error(label + " data array dimension mismatchs."); }

				const vtkio::tables::AttributeType attr_type = vtk_data.attr_type;
				const vtkio::tables::AttributeTypeInfo attr_info = vtkio::tables::getVTKAttributeTypeInfo(attr_type);
				const std::string attr_type_str = vtkio::tables::getAttributeTypeString(attr_type);
				if (!attr_info.supported) { throw std::invalid_argument(label + " " + attr_type_str + " attribute type not supported."); }
				if (dim > attr_info.max_dimensions) { throw std::invalid_argument(label + " " + " has more dimensions than allowed for its attribute type."); }
				if (dim < attr_info.min_dimensions) { throw std::invalid_argument(label + " " + " has less dimensions than allowed for its attribute type."); }
			}
		};
		checkVTKData(this->getNumberOfPoints(), this->point_data);
		checkVTKData(this->getNumberOfCells(), this->cell_data);
	}
	inline void VTKStream::clear()
	{
		this->points.clear();
		this->cells.clear();
		this->cell_types.clear();
		this->point_data.clear();
		this->cell_data.clear();
	}
	inline size_t VTKStream::_getDataDimensions(const bool point_data, const std::string label)
	{
		auto& entity_data = (point_data) ? this->point_data : this->cell_data;
		const size_t n_entities = (point_data) ? this->getNumberOfPoints() : this->getNumberOfCells();
		auto vtk_data_it = entity_data.find(label);
		if (vtk_data_it == entity_data.end()) { throw std::invalid_argument("Label not found in data."); }
		auto& vtk_data = vtk_data_it->second;
		return vtk_data.buffer.getNumberOfItems() / n_entities;
	}
	inline void VTKStream::setComments(const std::string comments)
	{
		if (comments.find('\n') != std::string::npos) { throw std::invalid_argument("Comments cannot contain '\n'"); }
		if (comments.length() > 256) { throw std::length_error("Comments cannot be larger than 256 characters."); }
		this->comments = comments;
	}
	inline size_t VTKStream::getNumberOfPoints()
	{
		return this->points.getNumberOfItems() / 3;
	}
	inline size_t VTKStream::getNumberOfCells()
	{
		return this->cell_types.getNumberOfItems();
	}
	inline std::string VTKStream::getComments()
	{
		return this->comments;
	}
	inline size_t VTKStream::getPointDataDimensions(const std::string label)
	{
		return this->_getDataDimensions(true, label);
	}
	inline size_t VTKStream::getCellDataDimensions(const std::string label)
	{
		return this->_getDataDimensions(false, label);
	}
	inline void vtkio::VTKStream::write(const std::string path, const bool binary)
	{
		// Input checking
		this->check();
		
		//// TODO: Check that path is correct and has correct extension. Create folders is necessary.
		//// NOTE: The iteration number is responsibility of the user or another method wrapper
		const std::string dst = path;

		// Open the file
		std::ofstream outfile(dst, std::ios::binary);
		if (!outfile) {
			throw std::invalid_argument("Cannot open the file " + dst);
		}

		// Header
		outfile << "# vtk DataFile Version 4.2\n";
		outfile << this->comments << '\n'; 
		outfile << ((binary) ? "BINARY\n" : "ASCII\n");
		outfile << "DATASET UNSTRUCTURED_GRID\n";

		// Points
		outfile << "POINTS " << this->getNumberOfPoints() << " " << vtkio::tables::getVTKDataTypeString(this->points.getDataType()) << "\n";
		if (binary) {
			this->points.toStreamBinary(outfile, ByteOrder::Big);
		}
		else {
			this->points.toStreamASCII(outfile);
		}
		outfile << "\n";

		// Cells
		const size_t n_items = this->cells.getNumberOfItems(); // Includes the n_nodes_per_cell
		outfile << "CELLS " << this->getNumberOfCells() << " " << n_items << "\n";
		if (binary) {
			this->cells.toStreamBinary(outfile, ByteOrder::Big);
		}
		else {
			this->cells.toStreamASCII(outfile);
		}
		outfile << "\n";

		// Cell types
		outfile << "CELL_TYPES " << this->getNumberOfCells() << "\n";
		if (binary) {
			this->cell_types.toStreamBinary(outfile, ByteOrder::Big);
		}
		else {
			this->cell_types.toStreamASCII(outfile);
		}
		outfile << "\n";

		// Point and cell data
		auto saveVTKData = [&](const std::string title, const size_t n_entities, std::unordered_map<std::string, VTKData>& data)
		{
			const size_t num_fields = data.size();
			if (num_fields != 0) {
				outfile << title << " " << n_entities << "\n";

				for (auto& key_value : data) {
					const std::string& label = key_value.first;
					VTKData& vtk_data = key_value.second;
					bytebuffer::ByteBuffer& byte_buffer = vtk_data.buffer;
					const vtkio::tables::AttributeType attr_type = vtk_data.attr_type;
					const vtkio::tables::AttributeTypeInfo attr_info = vtkio::tables::getVTKAttributeTypeInfo(attr_type);
					const std::string attr_type_str = vtkio::tables::getAttributeTypeString(attr_type);

					// Gather data
					const size_t dim = byte_buffer.getNumberOfItems() / n_entities;
					const std::string data_type_str = vtkio::tables::getVTKDataTypeString(byte_buffer.getDataType());

					// Write header
					switch (attr_type)
					{
					case vtkio::tables::AttributeType::Scalars:   outfile << "SCALARS " << label << " " << data_type_str << " " << dim << "\n" << "LOOKUP_TABLE default\n"; break;
					case vtkio::tables::AttributeType::Vectors:   outfile << "VECTORS " << label << " " << data_type_str << "\n"; break;
					case vtkio::tables::AttributeType::Tensors:   outfile << "TENSORS " << label << " " << data_type_str << "\n"; break;
					case vtkio::tables::AttributeType::Normals:   outfile << "NORMALS " << label << " " << data_type_str << "\n"; break;
					case vtkio::tables::AttributeType::FieldData: outfile << "FIELD FieldData 1\n" << label << " " << dim << " " << n_entities << " " << data_type_str << "\n"; break;
					default:
						throw std::invalid_argument(attr_type_str + " AttributeType not supported.");
						break;
					}

					// Write data
					if (binary) {
						byte_buffer.toStreamBinary(outfile, ByteOrder::Big);
					}
					else {
						byte_buffer.toStreamASCII(outfile);
					}
					outfile << "\n";
				}
			}
		};

		saveVTKData("POINT_DATA", this->getNumberOfPoints(), this->point_data);
		saveVTKData("CELL_DATA", this->getNumberOfCells(), this->cell_data);
	}
	inline void VTKStream::write_empty(const std::string path)
	{
		// Open the file
		std::ofstream outfile(path, std::ios::binary);
		if (!outfile) {
			std::cout << "Cannot open a file " << path << " to save a VTK mesh." << std::endl;
			exit(-1);
		}

		// Header
		outfile << "# vtk DataFile Version 4.2\n";
		outfile << "\n";
		outfile << "ASCII\n";
		outfile << "DATASET UNSTRUCTURED_GRID\n";
		outfile << "POINTS 0 double\n";
		outfile << "CELLS 0 0\n";
		outfile << "CELL_TYPES 0\n";

		outfile.close();
	};
	inline void VTKStream::read(const std::string path)
	{
		this->clear();

		// Open file
		std::ifstream input(path, std::ios::binary);
		if (!input) {
			std::cout << "Error: Cannot read file " << path << std::endl;
			exit(-1);
		}

		// Initialize buffers
		std::string line_buffer;
		std::string word_buffer;

		// Read header
		bool is_binary = false;
		{
			std::getline(input, line_buffer); // # vtk DataFile Version 4.1
			std::getline(input, line_buffer); // comments
			this->setComments(line_buffer);
			while (line_buffer.substr(0, 7) != "DATASET") {
				std::getline(input, line_buffer);
				if (line_buffer.substr(0, 5) == "ASCII") {
					is_binary = false;
				}
				else if (line_buffer.substr(0, 6) == "BINARY") {
					is_binary = true;
				}
			}

			// line_buffer is "DATASET" at this point
			if (line_buffer.substr(8, 17) != "UNSTRUCTURED_GRID") {
				throw std::invalid_argument("Only DATASET UNSTRUCTURED_GRID can be parsed.");
			}
		}
		// line_buffer is DATASET at this point

		// Read dataset
		{
			bool read_points = false;
			bool read_cells = false;
			bool read_cell_types = false;
			while (!read_points || !read_cells || !read_cell_types) {
				if (line_buffer.substr(0, 6) == "POINTS") {
					read_points = true;

					// Points header
					std::istringstream line_stream(line_buffer);
					std::string points_word, n_points_str, type_str;
					std::getline(line_stream, points_word, ' ');
					std::getline(line_stream, n_points_str, ' ');
					std::getline(line_stream, type_str);

					DataType points_type;
					if (type_str == "double") {
						points_type = DataType::Float64;
					}
					else if (type_str == "float") {
						points_type = DataType::Float32;
					}
					else {
						throw std::invalid_argument("Points can only be 'double' or 'float' in VTK.");
					}


					// Read the data
					if (is_binary) {
						const size_t n_bytes = getDataTypeSize(points_type) * std::stoi(n_points_str) * 3;
						this->points.setFromBinaryStream(input, points_type, n_bytes, ByteOrder::Big);
					}
					else {

						this->points.setFromASCIIStream(input, points_type, 3 * std::stoi(n_points_str), ' ');

					}
				}
				else if (line_buffer.substr(0, 5) == "CELLS") {
					read_cells = true;
					// Cells header
					std::istringstream line_stream(line_buffer);
					std::string cells_word, n_cells_str, total_n_items_str;
					std::getline(line_stream, cells_word, ' ');
					std::getline(line_stream, n_cells_str, ' ');
					std::getline(line_stream, total_n_items_str);


					// Read the data
					if (is_binary) {
						const size_t n_bytes = getDataTypeSize(DataType::Int32) * std::stoi(total_n_items_str);
						this->cells.setFromBinaryStream(input, DataType::Int32, n_bytes, ByteOrder::Big);
					}
					else {
						this->cells.setFromASCIIStream(input, DataType::Int32, std::stoi(total_n_items_str), ' ');
					}
				}
				else if (line_buffer.substr(0, 10) == "CELL_TYPES") {
					read_cell_types = true;

					// Cells header
					std::istringstream line_stream(line_buffer);
					std::string cell_types_word, n_cells_str;
					std::getline(line_stream, cell_types_word, ' ');
					std::getline(line_stream, n_cells_str, ' ');

					// Read the data
					if (is_binary) {
						const size_t n_bytes = getDataTypeSize(DataType::Int32) * std::stoi(n_cells_str);
						this->cell_types.setFromBinaryStream(input, DataType::Int32, n_bytes, ByteOrder::Big);
					}
					else {
						this->cell_types.setFromASCIIStream(input, DataType::Int32, std::stoi(n_cells_str), ' ');
					}
				}
				std::getline(input, line_buffer);

				// Infinite loop ?
			}
		}
		// At this point the cursor is right after the DATASET

		auto readData = [&](const bool point_data, const bool is_binary, const size_t n_entities, const std::string end_line) {
			auto readDataSeries = [&](const bool point_data, const bool is_binary, const std::string label, const vtkio::tables::AttributeType attr_type, const std::string data_type_str, const std::string dim_str, const size_t n_entities)
			{
				auto& vtk_data = (point_data) ? this->point_data[label] : this->cell_data[label];
				vtk_data.attr_type = attr_type;
				const DataType data_type = vtkio::tables::getDataTypeFromString(data_type_str);
				const size_t n_items_to_read = std::stoi(dim_str) * n_entities;

				if (is_binary) {
					const size_t n_bytes = getDataTypeSize(data_type) * n_items_to_read;
					vtk_data.buffer.setFromBinaryStream(input, data_type, n_bytes, ByteOrder::Big);
				}
				else {
					vtk_data.buffer.setFromASCIIStream(input, data_type, n_items_to_read, ' ');
				}
			};

			auto readFixedDimDataSeries = [&](const bool point_data, const bool is_binary, const std::string header, const vtkio::tables::AttributeType attr_type, const std::string dim_str, const size_t n_entities)
			{
				std::istringstream line_stream(header);
				std::string attr_type_word, label, data_type_str;
				std::getline(line_stream, attr_type_word, ' ');
				std::getline(line_stream, label, ' ');
				std::getline(line_stream, data_type_str);
				readDataSeries(point_data, is_binary, label, attr_type, data_type_str, dim_str, n_entities);
			};

			while (line_buffer.substr(0, end_line.length()) != end_line && !input.eof()) {
				if (line_buffer.substr(0, 7) == "SCALARS") {
					std::istringstream line_stream(line_buffer);
					std::string scalar_word, label, dim_str, data_type_str;
					std::getline(line_stream, scalar_word, ' ');
					std::getline(line_stream, label, ' ');
					std::getline(line_stream, data_type_str, ' ');
					std::getline(line_stream, dim_str);

					std::getline(input, line_buffer);
					if (line_buffer.substr(0, 20) != "LOOKUP_TABLE default") {
						throw std::invalid_argument("Only 'LOOKUP_TABLE default' supported.");
					}
					readDataSeries(point_data, is_binary, label, vtkio::tables::AttributeType::Scalars, data_type_str, dim_str, n_entities);
				}
				else if (line_buffer.substr(0, 7) == "VECTORS") {
					readFixedDimDataSeries(point_data, is_binary, line_buffer, vtkio::tables::AttributeType::Vectors, "3", n_entities);
				}
				else if (line_buffer.substr(0, 7) == "TENSORS") {
					readFixedDimDataSeries(point_data, is_binary, line_buffer, vtkio::tables::AttributeType::Tensors, "9", n_entities);
				}
				else if (line_buffer.substr(0, 7) == "NORMALS") {
					readFixedDimDataSeries(point_data, is_binary, line_buffer, vtkio::tables::AttributeType::Normals, "3", n_entities);
				}
				else if (line_buffer.substr(0, 5) == "FIELD") {
					// Note: Each entry in any field data is stripped from the hierarchy and just added in the flat data map

					std::istringstream line_stream(line_buffer);
					std::string field_word, field_data_word, n_fields_str;
					std::getline(line_stream, field_word, ' ');
					std::getline(line_stream, field_data_word, ' ');
					std::getline(line_stream, n_fields_str);

					// Different fields to read
					const size_t n_fields = std::stoi(n_fields_str);
					size_t read_fields = 0;
					while (read_fields < n_fields) {
						std::getline(input, line_buffer);
						if (line_buffer.length() != 0) {
							read_fields++;

							std::istringstream line_stream(line_buffer);
							std::string label, dim_str, n_entities_str, data_type_str;
							std::getline(line_stream, label, ' ');
							std::getline(line_stream, dim_str, ' ');
							std::getline(line_stream, n_entities_str, ' ');
							std::getline(line_stream, data_type_str);

							readDataSeries(point_data, is_binary, label, vtkio::tables::AttributeType::FieldData, data_type_str, dim_str, n_entities);
						}
					}
				}
				std::getline(input, line_buffer);
			}
		};

		// CELL_DATA or POINT_DATA can be first
		while (!input.eof()) {
			if (line_buffer.substr(0, 10) == "POINT_DATA") {
				readData(true, is_binary, this->getNumberOfPoints(), /* Escape line = */ "CELL_DATA");
			}
			else if (line_buffer.substr(0, 9) == "CELL_DATA") {
				readData(false, is_binary, this->getNumberOfCells(), /* Escape line = */ "POINT_DATA");
			}
			else {
				std::getline(input, line_buffer);
			}
		}

		this->check();
	}
	template<class InputIterator>
	inline void VTKStream::setPoints(InputIterator begin, InputIterator end, const size_t dim, const ByteOrder byte_order)
	{
		using T = typename std::iterator_traits<InputIterator>::value_type;
		static_assert(std::is_same_v<T, double> || std::is_same_v<T, float>, "Points must be of double or float type.");

		if ((dim == 0) || (dim > 3)) { throw std::invalid_argument("Points dimensions must be 1, 2 or 3."); }
		const size_t n = std::distance(begin, end);
		if (n == 0) { throw std::invalid_argument("Points input is empty."); }
		const size_t n_points = n / dim;
		if (n_points * dim != n) { throw std::invalid_argument("Points length and dimensions mismatch."); }

		if (dim == 3) {
			this->points.setFromIterator(begin, end, byte_order);
		}
		else {
			// Add zeros in the remaining dimensions
			std::vector<T> points3d;
			points3d.reserve(n_points * 3);
			auto it = begin;
			for (size_t p = 0; p < n_points; p++) {
				for (size_t i = 0; i < dim; i++) {
					points3d.push_back(*it);
					it++;
				}
				for (size_t i = dim; i < 3; i++) {
					points3d.push_back(T(0.0));
				}
			}
			this->points.setFromIterator(points3d.begin(), points3d.end(), byte_order);
		}
	}
	template<class VecContainer>
	inline void VTKStream::setPointsNestedIterator(VecContainer begin, VecContainer end, const size_t dim, const ByteOrder byte_order)
	{
		using T = typename Nested2Iterator<VecContainer>::nested_value_type;
		static_assert(std::is_same_v<T, double> || std::is_same_v<T, float>, "Points must be of double or float type.");

		if ((dim == 0) || (dim > 3)) { throw std::invalid_argument("Points dimensions must be 1, 2 or 3."); }
		const size_t n_points = std::distance(begin, end);
		if (n_points == 0) { throw std::invalid_argument("Points input is empty."); }

		if (dim == 3) {
			this->points.setFromNestedIterator(begin, end, 3*n_points, byte_order);
		}
		else {
			// Add zeros in the remaining dimensions
			std::vector<T> points3d;
			points3d.reserve(3* n_points);
			for (auto it = begin; it != end; it++) {
				for (size_t i = 0; i < dim; i++) {
					points3d.push_back((*it)[i]);
				}
				for (size_t i = dim; i < 3; i++) {
					points3d.push_back(T(0.0));
				}
			}
			this->points.setFromIterator(points3d.begin(), points3d.end(), byte_order);
		}

	}
	template<class InputIterator>
	inline void VTKStream::setCells(InputIterator begin, InputIterator end, const vtkio::tables::CellType cell_type, const ByteOrder byte_order)
	{
		using T = typename std::iterator_traits<InputIterator>::value_type;
		static_assert(std::is_same_v<T, int32_t>, "Cells must be of type int32_t.");

		const size_t nodes_per_cell = vtkio::tables::getVTKCellTypeInfo(cell_type).n_nodes;
		const size_t n = std::distance(begin, end);
		if (n == 0) { throw std::invalid_argument("Cells input is empty."); }
		const size_t n_cells = n / nodes_per_cell;
		if (n_cells * nodes_per_cell != n) { throw std::invalid_argument("Cells length and number of nodes mismatch."); }
		
		// Build VTK cells array
		std::vector<int32_t> cells;
		cells.reserve(n_cells * (nodes_per_cell + 1));
		for (auto it = begin; it != end; ) {
			cells.push_back(nodes_per_cell);
			for (size_t i = 0; i < nodes_per_cell; i++) {
				cells.push_back((int32_t)(*it));
				it++;
			}
		}
		this->cells.setFromIterator(cells.begin(), cells.end(), byte_order);

		// Element types
		std::vector cell_types(n_cells, static_cast<int>(cell_type));
		this->cell_types.setFromIterator(cell_types.begin(), cell_types.end());
	}
	template<class ElementIterator, class ElementTypeIterator>
	inline void VTKStream::setCells(ElementIterator cells_begin, ElementIterator cells_end, ElementTypeIterator cell_types_begin, ElementTypeIterator cell_types_end, const ByteOrder byte_order)
	{
		using T = typename std::iterator_traits<ElementIterator>::value_type;
		static_assert(std::is_same_v<T, int32_t>, "Cells must be of type int32_t.");
		using T2 = typename std::iterator_traits<ElementTypeIterator>::value_type;
		static_assert(std::is_same<T2, vtkio::tables::CellType>::value, "ElementTypeIterator doesn't iterate over ElementTypes.");

		const size_t n_cells = std::distance(cell_types_begin, cell_types_end);
		if (n_cells == 0) { throw std::invalid_argument("Cells input is empty."); }

		// Build VTK cells array
		std::vector<int32_t> cells;
		cells.reserve(n_cells + std::distance(cells_begin, cells_end));
		std::vector<int> cell_types;
		cell_types.reserve(n_cells);
		auto it = cells_begin;
		for (auto types_it = cell_types_begin; types_it != cell_types_end; types_it++) {
			const size_t nodes_per_cell = vtkio::tables::getVTKCellTypeInfo(*types_it).n_nodes;
			cell_types.push_back(static_cast<int>(*types_it));
			cells.push_back(nodes_per_cell);
			for (size_t i = 0; i < nodes_per_cell; i++) {
				cells.push_back((int32_t)(*it));
				it++;
			}
		}
		if (it != cells_end) { throw std::invalid_argument("Element iterator mismatch with cell types"); }
		this->cells.setFromIterator(cells.begin(), cells.end(), byte_order);
		this->cell_types.setFromIterator(cell_types.begin(), cell_types.end());
	}
	template<class OutputIterator>
	inline void VTKStream::getPoints(OutputIterator begin, OutputIterator end, const size_t dim, const ByteOrder byte_order)
	{
		using T = typename std::iterator_traits<OutputIterator>::value_type;
		this->points.throwIfNotType<T>();

		const size_t n = std::distance(begin, end);
		if (n < dim * this->getNumberOfPoints()) { throw std::invalid_argument("Cannot return points. Too small output container."); }
		if ((dim == 0) || (dim > 3)) { throw std::invalid_argument("Points dimensions must be 1, 2 or 3."); }


		if (dim == 3) {
			this->points.getDataCopy(begin, end, byte_order);
		}
		else {
			auto out_it = begin;
			T* points_it = this->points.getDataPtr<T>();
			for (size_t p = 0; p < this->getNumberOfPoints(); p++) {
				for (size_t i = 0; i < dim; i++) {
					*out_it = *(points_it + 3 * p + i);
					out_it++;
				}
			}
		}
	}
	template<class OutputVecIterator>
	inline void VTKStream::getPointsNestedIterator(OutputVecIterator begin, OutputVecIterator end, const size_t dim, const ByteOrder byte_order)
	{
		using T = typename Nested2Iterator<OutputVecIterator>::nested_value_type;
		this->points.throwIfNotType<T>();

		const size_t n = std::distance(begin, end);
		if (n < this->getNumberOfPoints()) { throw std::invalid_argument("Cannot return points. Too small output container."); }
		if ((dim == 0) || (dim > 3)) { throw std::invalid_argument("Points dimensions must be 1, 2 or 3."); }

		if (dim == 3) {
			this->points.getDataCopyNestedIterator(begin, end, byte_order);
		}
		else {
			auto vec_it = begin;
			T* points_it = this->points.getDataPtr<T>();
			for (size_t p = 0; p < this->getNumberOfPoints(); p++) {
				auto inner_it = vec_it->begin();
				for (size_t i = 0; i < dim; i++) {
					*inner_it = *(points_it + 3 * p + i);
					inner_it++;
				}
				vec_it++;
			}
		}
	}
	template<class OutputIterator>
	inline void VTKStream::getCells(OutputIterator begin, OutputIterator end)
	{
		using T = typename std::iterator_traits<OutputIterator>::value_type;
		static_assert(std::is_same_v<T, int32_t>, "Cells must be of type int32_t.");

		const size_t n = std::distance(begin, end);
		if (n < this->getNumberOfCells()) { throw std::invalid_argument("Cannot return cells. Too small output container."); }

		// Build VTK cells array
		this->cells.swap(ByteOrder::Native);
		int32_t* cells_begin = this->cells.getDataPtr<int32_t>();
		auto output_it = begin;
		for (auto it = cells_begin; it != (cells_begin + this->getNumberOfCells()); it++) {
			const size_t nodes_per_cell = *it;
			it++;
			for (size_t i = 0; i < nodes_per_cell; i++) {
				*output_it = *it;
				output_it++;
				it++;
			}
		}
	}
	template<class OutputNestedIterator>
	inline void VTKStream::getCellsNestedIterator(OutputNestedIterator begin, OutputNestedIterator end)
	{
		using T = typename Nested2Iterator<OutputNestedIterator>::nested_value_type;
		static_assert(std::is_same_v<T, int32_t>, "Cell Iterator must contain int32_t");
		if (this->getNumberOfCells() > (size_t)std::distance(begin, end)) { throw std::invalid_argument("Cell container is too short."); }

		this->cells.swap(ByteOrder::Native);
		int32_t* cell_it = this->cells.getDataPtr<int32_t>();
		auto outer_it = begin;
		for (size_t cell_i = 0; cell_i < this->getNumberOfCells(); cell_i++) {
			const size_t nodes_per_cell = *cell_it;
			cell_it++;

			const size_t inner_size = std::distance(outer_it->begin(), outer_it->end());
			if (nodes_per_cell > inner_size) { throw std::invalid_argument("Cell container [" + std::to_string(cell_i) + "] is too short."); }

			auto inner_it = outer_it->begin();
			for (size_t node_i = 0; node_i < nodes_per_cell; node_i++) {
				*inner_it = *cell_it;
				inner_it++;
				cell_it++;
			}

			outer_it++;
		}
	}
	template<class NestedIterator>
	inline void VTKStream::setCellsNestedIterator(NestedIterator begin, NestedIterator end, const vtkio::tables::CellType cell_type, const ByteOrder byte_order)
	{
		using T = typename Nested2Iterator<NestedIterator>::nested_value_type;
		throwIfNumberTypeNotSupported<T>();

		const size_t n_cells = std::distance(begin, end);
		const int32_t nodes_per_cell = (int32_t)vtkio::tables::getVTKCellTypeInfo(cell_type).n_nodes;
		
		// Build VTK cells array
		std::vector<int32_t> cells;
		cells.reserve(n_cells * (nodes_per_cell + 1));
		for (auto outer_it = begin; outer_it != end; outer_it++) {
			cells.push_back(nodes_per_cell);
			for (size_t i = 0; i < nodes_per_cell; i++) {
				cells.push_back( (int32_t)(*outer_it)[i] );
			}
		}
		this->cells.setFromIterator(cells.begin(), cells.end(), byte_order);

		// Element types
		std::vector cell_types(n_cells, static_cast<int>(cell_type));
		this->cell_types.setFromIterator(cell_types.begin(), cell_types.end());
	}
	template<class ElementNestedIterator, class ElementTypeIterator>
	inline void VTKStream::setCellsNestedIterator(ElementNestedIterator cells_begin, ElementNestedIterator cells_end, ElementTypeIterator cell_types_begin, ElementTypeIterator cell_types_end, const ByteOrder byte_order)
	{
		using T = typename Nested2Iterator<ElementNestedIterator>::nested_value_type;
		using T2 = typename std::iterator_traits<ElementTypeIterator>::value_type;
		static_assert(std::is_same<T2, vtkio::tables::CellType>::value, "ElementTypeIterator doesn't iterate over ElementTypes.");

		const size_t n_cells = std::distance(cell_types_begin, cell_types_end);
		if (n_cells == 0) { throw std::invalid_argument("Cells input is empty."); }

		// Build VTK cells array
		std::vector<int32_t> cells;
		cells.reserve(2* n_cells); // Minimum possible size (particles)
		std::vector<int> cell_types;
		cell_types.reserve(n_cells);
		auto it = cells_begin;
		for (auto types_it = cell_types_begin; types_it != cell_types_end; types_it++) {
			const size_t nodes_per_cell = vtkio::tables::getVTKCellTypeInfo(*types_it).n_nodes;
			cell_types.push_back(static_cast<int>(*types_it));
			cells.push_back(nodes_per_cell);
			for (size_t i = 0; i < nodes_per_cell; i++) {
				cells.push_back((*it)[i]);
				it++;
			}
		}
		if (it != cells_end) { throw std::invalid_argument("Element iterator mismatch with cell types"); }
		this->cells.setFromIterator(cells.begin(), cells.end(), byte_order);
		this->cell_types.setFromIterator(cell_types.begin(), cell_types.end());
	}
	template<class InputIterator>
	inline void VTKStream::_setData(const bool point_data, const std::string label, InputIterator begin, InputIterator end, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order)
	{
		// I leave this here as an example
		// CAN WE PUT THIS INTO A FUNCTION /////////////////////////////////////////////////////////////
		using T = typename std::iterator_traits<InputIterator>::value_type;
		if constexpr (!isTypeSupported<T>()) {
			using T_nested = typename Nested2Iterator<InputIterator>::nested_value_type;
			if constexpr (isTypeSupported<T_nested>()) {
				static_assert(!std::is_same<T, T>::value, "Error: you passed a nested iterator to a flat iterator function.");
			}
		}
		throwIfTypeNotSupported<T>();
		// CAN WE PUT THIS INTO A FUNCTION /////////////////////////////////////////////////////////////

		const size_t n_entities = (point_data) ? this->getNumberOfPoints() : this->getNumberOfCells();
		const size_t n = std::distance(begin, end);
		const size_t dim = n / n_entities;
		const size_t max_dim = vtkio::tables::getVTKAttributeTypeInfo(attr_type).max_dimensions;

		if (n == 0) { throw std::invalid_argument("Data input is empty."); }
		if ((dim == 0) || (dim > max_dim)) { throw std::invalid_argument("Data attribute (" + std::to_string(static_cast<int>(attr_type)) + " dimension must be <= " + std::to_string(max_dim)); }
		if (n_entities * dim != n) { throw std::invalid_argument("Data length and dimensions mismatch with the number of points or cells."); }

		auto &vtk_data = (point_data) ? this->point_data[label] : this->cell_data[label];
		vtk_data.attr_type = attr_type;
		vtk_data.buffer.setFromIterator(begin, end, byte_order);
	}
	template<class VecContainer>
	inline void VTKStream::_setDataNestedIterator(const bool point_data, const std::string label, VecContainer begin, VecContainer end, const size_t dim, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order)
	{
		using T = typename Nested2Iterator<VecContainer>::nested_value_type;
		throwIfTypeNotSupported<T>();

		const size_t n_entities = (point_data) ? this->getNumberOfPoints() : this->getNumberOfCells();
		const size_t n = std::distance(begin, end);
		const size_t max_dim = vtkio::tables::getVTKAttributeTypeInfo(attr_type).max_dimensions;

		if (n == 0) { throw std::invalid_argument("Data input is empty."); }
		if ((dim == 0) || (dim > max_dim)) { throw std::invalid_argument("Data attribute (" + std::to_string(static_cast<int>(attr_type)) + " dimension must be <= " + std::to_string(max_dim)); }
		if (n_entities != n) { throw std::invalid_argument("Data length and dimensions mismatch with the number of points or cells."); }

		auto& vtk_data = (point_data) ? this->point_data[label] : this->cell_data[label];
		vtk_data.attr_type = attr_type;
		vtk_data.buffer.setFromNestedIterator(begin, end, n*dim, byte_order);
	}
	template<class OutputIterator>
	inline void VTKStream::_getData(const bool point_data, const std::string label, OutputIterator begin, OutputIterator end, vtkio::tables::AttributeType &attr_type, const ByteOrder byte_order)
	{
		auto& entity_data = (point_data) ? this->point_data : this->cell_data;
		auto vtk_data_it = entity_data.find(label);
		if (vtk_data_it == entity_data.end()) { throw std::invalid_argument("Label '" + label + "' not found in data."); }
		auto& vtk_data = vtk_data_it->second;

		using T = typename std::iterator_traits<OutputIterator>::value_type;
		vtk_data.buffer.throwIfNotType<T>();

		const size_t n_entities = (point_data) ? this->getNumberOfPoints() : this->getNumberOfCells();
		const size_t dim = this->_getDataDimensions(point_data, label);
		const size_t n = std::distance(begin, end);
		if (n_entities * dim > n) { throw std::invalid_argument("Data container is too short."); }

		attr_type = vtk_data.attr_type;
		vtk_data.buffer.getDataCopy(begin, end, byte_order);
	}
	template<class OutputVecIterator>
	inline void VTKStream::_getDataVecIterator(const bool point_data, const std::string label, OutputVecIterator begin, OutputVecIterator end, vtkio::tables::AttributeType& attr_type, const ByteOrder byte_order)
	{
		auto& entity_data = (point_data) ? this->point_data : this->cell_data;
		auto vtk_data_it = entity_data.find(label);
		if (vtk_data_it == entity_data.end()) { throw std::invalid_argument("Label '" + label + "' not found in data."); }
		auto& vtk_data = vtk_data_it->second;

		using T = typename Nested2Iterator<OutputVecIterator>::nested_value_type;
		vtk_data.buffer.throwIfNotType<T>();

		const size_t n_entities = (point_data) ? this->getNumberOfPoints() : this->getNumberOfCells();
		const size_t dim = this->_getDataDimensions(point_data, label);
		const size_t n = std::distance(begin, end);
		if (n_entities > n) { throw std::invalid_argument("Data container is too short."); }

		attr_type = vtk_data.attr_type;
		vtk_data.buffer.swap(byte_order);
		T* buffer_it = vtk_data.buffer.getDataPtr<T>();
		for (size_t i = 0; i < n_entities; i++) {
			for (size_t j = 0; j < dim; j++) {
				(*(begin + i))[j] = (*buffer_it);
				buffer_it++;
			}
		}
	}
	template<class InputIterator>
	inline void VTKStream::setPointData(const std::string label, InputIterator begin, InputIterator end, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order)
	{
		this->_setData(true, label, begin, end, attr_type, byte_order);
	}
	template<class VecContainer>
	inline void VTKStream::setPointDataNestedIterator(const std::string label, VecContainer begin, VecContainer end, const size_t dim, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order)
	{
		this->_setDataNestedIterator(true, label, begin, end, dim, attr_type, byte_order);
	}
	template<class InputIterator>
	inline void VTKStream::setCellData(const std::string label, InputIterator begin, InputIterator end, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order)
	{
		this->_setData(false, label, begin, end, attr_type, byte_order);
	}
	template<class VecContainer>
	inline void VTKStream::setCellDataNestedIterator(const std::string label, VecContainer begin, VecContainer end, const size_t dim, const vtkio::tables::AttributeType attr_type, const ByteOrder byte_order)
	{
		this->_setDataNestedIterator(false, label, begin, end, dim, attr_type, byte_order);
	}
	template<class OutputIterator>
	inline void VTKStream::getCellsTypes(OutputIterator begin, OutputIterator end)
	{
		using T = typename std::iterator_traits<OutputIterator>::value_type;
		static_assert(std::is_same_v<T, int32_t> || std::is_same_v<T, vtkio::tables::CellType>, "CellTypes must be of type int32_t or vtkio::tables::CellTypes.");

		const size_t n_cells = this->getNumberOfCells();
		const size_t n = std::distance(begin, end);
		if (n_cells > n) { throw std::invalid_argument("Output cell type container is too short."); }

		int32_t* cell_types_it = this->cell_types.getDataPtr<int32_t>();
		for (size_t cell_i = 0; cell_i < n_cells; cell_i++) {
			*(begin + cell_i) = static_cast<T>(*(cell_types_it + cell_i));
		}
	}
	template<class OutputIterator>
	inline void VTKStream::getPointData(const std::string label, OutputIterator begin, OutputIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order)
	{
		this->_getData(true, label, begin, end, attr_type_out, byte_order);
	}
	template<class OutputVecIterator>
	inline void VTKStream::getPointDataVecIterator(const std::string label, OutputVecIterator begin, OutputVecIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order)
	{
		this->_getDataVecIterator(true, label, begin, end, attr_type_out, byte_order);
	}
	template<class OutputIterator>
	inline void VTKStream::getCellData(const std::string label, OutputIterator begin, OutputIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order)
	{
		this->_getData(false, label, begin, end, attr_type_out, byte_order);
	}
	template<class OutputVecIterator>
	inline void VTKStream::getCellDataVecIterator(const std::string label, OutputVecIterator begin, OutputVecIterator end, vtkio::tables::AttributeType& attr_type_out, const ByteOrder byte_order)
	{
		this->_getDataVecIterator(false, label, begin, end, attr_type_out, byte_order);
	}
}


