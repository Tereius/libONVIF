#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>


void findDerived(std::vector<std::string> &result, const std::map<std::string, std::string> &map, std::string derivedFrom) {

	for(std::map<std::string, std::string>::const_iterator it = map.begin(); it != map.end(); ++it) {
		if(it->second.compare(derivedFrom) == 0) {
			result.push_back(it->first);
			findDerived(result, map, it->first);
		}
	}
}

int main(int argc, const char **argv) {

	if(argc != 2) {
		return 1;
	}

	char lineChars[2048];

	std::ifstream ifs;
	ifs.open(argv[1], std::ifstream::in);
	if(!ifs.is_open()) {
		return 2;
	}

	std::map<std::string, std::string> nsMap;
	std::map<std::string, std::string> typedefs;
	std::vector<std::string> stringDerivedTypes;


	const std::string nsIdent("#define SOAP_NAMESPACE_OF_");
	const std::string typedefIdent("typedef ");

	while(!ifs.eof()) {
		ifs.getline(lineChars, 2048);
		std::string line(lineChars);

		// Parse nsmap
		{
			size_t posPrefixBegin = line.find(nsIdent);
			size_t posNsBegin = line.find("\"");
			if(posPrefixBegin != std::string::npos && posNsBegin != std::string::npos) {
				std::string prefix = line.substr(posPrefixBegin + nsIdent.size(), posNsBegin - posPrefixBegin - nsIdent.size());
				prefix.erase(remove_if(prefix.begin(), prefix.end(), isspace), prefix.end());

				std::string ns = line.substr(posNsBegin + 1, line.size() - posNsBegin - 2);
				nsMap[prefix] = ns;
			}
		}

		// Parse typedefs
		{
			size_t posTypedefBegin = line.find(typedefIdent);
			if(posTypedefBegin != std::string::npos) {

				size_t posToBegin = posTypedefBegin + typedefIdent.size();

				if(posToBegin != std::string::npos) {

					size_t posFromBegin = line.find(" ", posToBegin);

					if(posFromBegin != std::string::npos) {

						size_t posFromEnd = line.find(" ", posFromBegin + 1);

						if(posFromEnd == std::string::npos) {
							posFromEnd = line.find(";", posFromBegin);
						}

						if(posFromEnd != std::string::npos) {

							std::string fromType = line.substr(posToBegin, posFromBegin - posToBegin);
							fromType.erase(remove_if(fromType.begin(), fromType.end(), isspace), fromType.end());
							std::string toType = line.substr(posFromBegin, posFromEnd - posFromBegin);
							toType.erase(remove_if(toType.begin(), toType.end(), isspace), toType.end());
							typedefs[toType] = fromType;
						}
					}
				}
			}
		}
	};

	ifs.close();

	// Resolve string derived classes
	{
		findDerived(stringDerivedTypes, typedefs, "xsd__string");

		std::ofstream ofs;
		ofs.open("GsoapResolver.h", std::ifstream::out | std::ifstream::trunc);
		if(!ofs.is_open()) {
			return 3;
		}

		ofs << "#pragma once" << std::endl << std::endl << std::endl;
		ofs << "class GsoapResolver {" << std::endl;
		ofs << "public:" << std::endl;

		ofs << "	static bool isStringDerived(const QString &rQname) {" << std::endl;
		ofs << "		if(rQname.isEmpty()) return false;" << std::endl;
		for(std::vector<std::string>::const_iterator it = stringDerivedTypes.begin(); it != stringDerivedTypes.end(); ++it) {
			size_t posTypeEnd = it->find("__");
			std::string name = it->substr(posTypeEnd + 2, it->size() - posTypeEnd);
			std::string type = it->substr(0, posTypeEnd);
			ofs << "		else if(rQname == \"" << type << ":"  << name << "\") return true;" << std::endl;
		}
		ofs << "		else return false;" << std::endl;
		ofs << "	}" << std::endl;
		ofs << "};" << std::endl;

		ofs.close();
	}

	return 0;
};
