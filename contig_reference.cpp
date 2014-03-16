#include "api/BamReader.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unistd.h>


using namespace BamTools;
using namespace std;

void insert_read(BamAlignment &ba, map<pair<string,string>,int> &crc, BamReader &r)
{
	string ref_name;

	auto first = ba.Name.find("gi|"); 
	if (ba.RefID != -1) {
		ref_name = r.GetReferenceData()[ba.RefID].RefName;
	} else {
		ref_name = "unmapped";
	}
	pair<string,string> p = 
		make_pair(	ref_name, 
					ba.Name.substr(first+3,(ba.Name.find("|",first+3) - first)-3));
	crc.insert(make_pair(p,0));
	crc[p]++;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {cout << "Need bam files!"; return -1;}

	vector<string> bam_files(argv+1,argv+1 + (argc -1));
	BamReader reader;
	BamAlignment ba;

	map<pair<string,string>,int> contigs_refs_count;

	string bam_file = "/home/binni/Programming/uppmax/2013-01-18_seed0_CPUs16_sorted.fasta/bowtie2_md/asm_pair-smds.bam";

	for (auto bam_file : bam_files) {
		if ( !reader.Open(bam_file) ) {
			cerr << "Could not open input BAM files." << endl;
			return -1;
		}
		const RefVector r = reader.GetReferenceData();
		while (reader.GetNextAlignment(ba)) {
			insert_read(
				ba,
				contigs_refs_count,
				reader);
			//refids.insert(ba.RefID);
		}
		reader.Close();
	}
	cout << "contig_id"<<"\t"<<"ref_id"<<"\t"<<"count"<<endl;
	for (auto contig : contigs_refs_count) {

		cout << contig.first.first << "\t" << contig.first.second << "\t" << contig.second << endl;
	}
	//cout << refids.size()  << endl;
//	RefVector rv = reader.GetReferenceData();
//	for (auto i : rv){
//		cout <<  i.RefName << endl;
//	}
	return 0;
}