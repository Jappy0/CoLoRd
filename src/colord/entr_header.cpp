#include "entr_header.h"
//#include "ppmd_stream.h"

// *******************************************************************************************
void CEntrComprHeaders::Compress()
{
	header_pack_t headers_pack;
	std::vector<uint8_t> v_output;

	id_coder.Init(true, headerComprMode, compression_level);

	while (headers_queue.Pop(headers_pack))
	{
		for (const auto& [id, plus_id] : headers_pack)
			id_coder.Encode(plus_id == qual_header_type::eq_read_header, id);

		id_coder.Finish();

		id_coder.GetOutput(v_output);
		id_coder.Restart();

		uint32_t n_reads = static_cast<uint32_t>(headers_pack.size());

		archive.AddPart(s_header, v_output, n_reads);
		v_output.clear();
	}
}

// *******************************************************************************************
void CEntrDecomprHeaders::Decompress()
{
	std::vector<uint8_t> v_input, v_compressed;
	size_t n_reads;
	header_pack_t pack;

	id_coder.Init(false, headerComprMode, compression_level);

	string id;
	bool plus_id;

	while (archive.GetPart(s_header, v_compressed, n_reads))
	{
		id_coder.SetInput(v_compressed);
		id_coder.Restart();

		for (uint32_t i = 0; i < n_reads; ++i)
		{
			id_coder.Decode(plus_id, id);
			pack.emplace_back(std::move(id), plus_id ? qual_header_type::eq_read_header : qual_header_type::empty);
		}

		id_coder.Finish();

		header_decompr_queue.Push(std::move(pack));
	}

	/*if (pack.size())
		header_decompr_queue.Push(std::move(pack));*/
	header_decompr_queue.MarkCompleted();
}

// EOF
