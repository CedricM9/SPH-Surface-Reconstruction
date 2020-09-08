#include "happly.h"

int main() {

    // Create data
    std::vector<float> elementA_prop1(20, 100);
    std::vector<int> elementA_prop2(20, 11);
    std::vector<std::vector<double>> elementB_listProp;
    std::vector<double> list(10, 10);
    for (int i = 0; i < 42; ++i) elementB_listProp.push_back(list);

    // Create mesh data
    std::vector<std::array<double, 3>> meshVertexPositions(3, std::array<double,3>({0, 2, 3}));
    std::vector<std::array<double, 3>> meshVertexColors(3, std::array<double,3>({255, 0, 0}));
    std::vector<std::vector<size_t>> meshFaceIndices;
    meshFaceIndices.push_back({0, 1, 2});

    // Create an empty object
    happly::PLYData plyOut;

    // Add elements
    plyOut.addElement("elementA", 20);
    plyOut.addElement("elementB", 42);

    // Add properties to those elements
    plyOut.getElement("elementA").addProperty<float>("prop1", elementA_prop1);
    plyOut.getElement("elementA").addProperty<int>("prop2", elementA_prop2);
    plyOut.getElement("elementB").addListProperty<double>("listprop1", elementB_listProp);

    // Add mesh data (elements are created automatically)
    plyOut.addVertexPositions(meshVertexPositions);
    plyOut.addVertexColors(meshVertexColors);
    plyOut.addFaceIndices(meshFaceIndices);

    // Write the object to file
    plyOut.write("my_output_file.ply", happly::DataFormat::ASCII);

}
