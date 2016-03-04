#include "CrackBinaryDataset.h"

void main()
{
	std::string filefolder = "C:\\Users\\Leo\\Desktop\\Samples\\train";
	BinaDataset binData;
	std::vector<std::string> fileLists = binData.getFileLists(filefolder); // load file name
	
	const int size_list = fileLists.size();
	std::cout << "image count: " << size_list << std::endl;
	
	std::vector<int> image_labels(size_list, 0);  // generate lables, here are all 0
	
	std::string binfile = "C:\\Users\\Leo\\Desktop\\Samples\\train.bin";
	binData.images2BinaryFile( filefolder, fileLists, image_labels, binfile );
}
