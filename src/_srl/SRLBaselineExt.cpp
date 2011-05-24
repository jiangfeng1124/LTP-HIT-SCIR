#include "SRLBaselineExt.h"
#include "Configuration.h"
#include "FeatureExtractor.h"

//////////////////////////////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
SRLBaselineExt::SRLBaselineExt(const DataPreProcess* dataPreProc, 
							   const FeaturesMethod* featMethod)
							   : SRLBaseline(dataPreProc, featMethod)
{

}

//////////////////////////////////////////////////////////////////////////
SRLBaselineExt::~SRLBaselineExt()
{

}


//////////////////////////////////////////////////////////////////////////
// method
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void SRLBaselineExt::ExtractFeatures(VecFeatForSent& vecAllFeatures, 
									 VecPosForSent& vecAllPos) const
{
    vecAllFeatures.clear();
    vecAllPos.clear();

	//first: extract the ConsFeatures for all the nodes
	//--------------------------------------//
	// node 1: feat1 feat2 feat3 ... featm
	// node 2: feat1 feat2 feat3 ... featm
	// ...
	// node n: feat1 feat2 feat3 ... featm
	//-------------------------------------//
	VecFeatForVerb vecFeatAllCons;	
	ExtractConsFeatures(vecFeatAllCons);

	/*cout << "vecFeatAllCons" << endl;
	for (VecFeatForVerb::iterator itForCons = vecFeatAllCons.begin(); itForCons != vecFeatAllCons.end(); ++itForCons)
	{
		for (VecFeatForCons::iterator itForFeat = (*itForCons).begin(); itForFeat != (*itForCons).end(); ++itForFeat)
		{
			cout << *itForFeat << " ";
		}
		cout << endl;
	}*/

	//second:extract the PdFeatures for all the predicate
	//--------------------------------------//
	// predicate 1: feat1 feat2 feat3 ... featm
	// predicate 2: feat1 feat2 feat3 ... featm
	// ...
	// predicate n: feat1 feat2 feat3 ... featm
	//--------------------------------------//
	VecFeatForVerb vecFeatAllPd;
	ExtractPdFeatures(vecFeatAllPd);

	/*cout << "vecFeatAllPd" << endl;
	for (VecFeatForVerb::iterator itForPd = vecFeatAllPd.begin(); itForPd != vecFeatAllPd.end(); ++itForPd)
	{
		for (VecFeatForCons::iterator itForFeat = (*itForPd).begin(); itForFeat != (*itForPd).end(); ++itForFeat)
		{
			cout << *itForFeat << " ";
		}
		cout << endl;
	}*/

	//finally: extract the ConsPdRelFeatures for the unFiltered nodes
	int pdIndex;
	vector<int>::const_iterator itPredicate;

	pdIndex = 0;
	itPredicate = m_vecPredicate.begin(); 
	while (itPredicate != m_vecPredicate.end())
	{
		int predID;
		VecFeatForVerb vecFeatVerb;
		VecPosForVerb vecPosVerb;

		predID = *itPredicate;

		cout << "predID: " << predID << endl;

		for (int nodeID = 0; nodeID < m_dataPreProc->m_intItemNum; nodeID++)
		{
			if (!IsFilter(nodeID, predID))
			{
				//1. extract the ConsPdRelFeatures for the unFiltered nodes
				VecFeatForCons vecFeatConsPd;
				ConsPdRelFeaturesExt consPdRelFeat(m_dataPreProc, nodeID, predID);

				m_featMethod->ExtractConsPdRelFeat(vecFeatConsPd, &consPdRelFeat);

				//1.5. extract the combine features, add by hjliu at 2007-4.23
				AllTypesFeatures allTypeFeat(m_dataPreProc, nodeID, predID);
				VecFeatForCons vecFeatComb;
				m_featMethod->ExtractCombFeat(vecFeatComb, &allTypeFeat);

				//2. add the ConsFeatures of unFiltered node to the vector - vecFeatVerb
				vecFeatConsPd.insert(vecFeatConsPd.end(), vecFeatAllCons.at(nodeID).begin(), vecFeatAllCons.at(nodeID).end());

				//3. add the PdFeatures of unFiltered node to the vector - vecFeatVerb
				vecFeatConsPd.insert(vecFeatConsPd.end(), vecFeatAllPd.at(pdIndex).begin(), vecFeatAllPd.at(pdIndex).end());

				//3.5 add the combine features of unFiltered node to the vector
				vecFeatConsPd.insert(vecFeatConsPd.end(), vecFeatComb.begin(), vecFeatComb.end());

				//4. push_back the vecFeatCons to vecFeatVerb
				vecFeatVerb.push_back(vecFeatConsPd);

				//5. get position of unFiltered nodes, and push_back to vecPosVerb
				DepNode curNode;
				m_dataPreProc->m_myTree->GetNodeValue(curNode, nodeID);
				vecPosVerb.push_back(curNode.constituent);
			}
		} //for - for each node corresponding to the predicate

		//features and position of the nodes corresponding to the predicate
		vecAllFeatures.push_back(vecFeatVerb);
		vecAllPos.push_back(vecPosVerb);

		pdIndex++;
		itPredicate++;
	} //while - for each predicate

	cout << "vecAllFeatures" << endl;
	for (VecFeatForSent::iterator itForAllFeat = vecAllFeatures.begin(); itForAllFeat != vecAllFeatures.end(); ++itForAllFeat)
	{
		for (VecFeatForVerb::iterator itForVerb = (*itForAllFeat).begin(); itForVerb != (*itForAllFeat).end(); ++itForVerb)
		{
			for (VecFeatForCons::iterator itForCons = (*itForVerb).begin(); itForCons != (*itForVerb).end(); ++itForCons)
				cout << *itForCons << " ";
			cout << endl;
		}
		cout << endl;
	}
	
	cout << "vecAllPos" << endl;
	for (VecPosForSent::iterator itForAllPos = vecAllPos.begin(); itForAllPos != vecAllPos.end(); ++itForAllPos)
	{
		for (VecPosForVerb::iterator itForVerb = (*itForAllPos).begin(); itForVerb != (*itForAllPos).end(); ++itForVerb)
		{
			cout << (*itForVerb).first << " ";
			cout << (*itForVerb).second << endl;
		}
		cout << endl;
	}
}

//Feature extracting method used in CoNLL2009. 
//add by jiangfeng. 2010.1.31
void SRLBaselineExt::conll_ExtractFeatures(VecFeatForSent& vecAllFeatures, VecPosForSent& vecAllPos) const
{
	vecAllFeatures.clear();
	vecAllPos.clear();

	// define the path of configure file
	string config_xml = "Chinese.xml";
	Configuration     configuration(config_xml);
    FeatureExtractor  feature_extractor(configuration);
	FeatureCollection feature_collection;
	vector<int>       feature_numbers;
    vector<string>    feature_prefixes;

	get_feature_config(feature_collection, feature_numbers, feature_prefixes, configuration);
	Sentence sentence;

	map<int, int> feat_number_index;
	feat_number_index.clear();

	for (size_t k = 0; k < feature_numbers.size(); ++k)
	{
		feat_number_index[feature_numbers[k]] = k;
	}

	/*open "conll2009-arg.conf" to get features to be selected*/
	string select_config = "conll2009-arg.conf";
	vector< vector<string> > m_select_features;
	open_select_config(select_config, m_select_features);

	vector<string> lines;
	construct_lines(lines);
	
	sentence.from_corpus_block(lines, configuration);
    const size_t predicate_count = sentence.get_predicates().size();
    const size_t row_count       = sentence.get_row_count();

    feature_extractor.set_target_sentence(sentence);
    vector<string> feature_values;
	vector< vector<string> > all_feature_values;

    // loop for each predicate
    for (size_t predicate_index = 0; predicate_index < predicate_count; ++predicate_index)
    {
		VecFeatForVerb vecFeatAllCons;
		VecFeatForCons vecForCons;
		VecPosForVerb vecPosVerb;

        int predID = m_vecPredicate[predicate_index];
        all_feature_values.clear();

        // calculate features
        feature_extractor.calc_features(predicate_index);

        // loop for each feature
		for (size_t i = 0; i < feature_numbers.size(); ++i)
		{
			const int feature_number     = feature_numbers[i];
			const string& feature_prefix = feature_prefixes[i];
			bool feature_empty_flag = false;
			try
			{
				feature_extractor.get_feature_for_rows(feature_number, feature_values);
			}
			catch (...)
			{
				feature_empty_flag = true;
			}

			if (feature_empty_flag)
			{
				feature_values.clear();
				// loop for each row
				for (size_t row = 1; row <= row_count; ++row)
				{
					feature_values.push_back("");
				}
			}
			
			all_feature_values.push_back(feature_values);
		}

		for (size_t row = 1; row <= row_count; ++row)
		{
			vecForCons.clear();
		    if (IsFilter(row-1, predID))
                continue;
			for (size_t i = 0; i < m_select_features.size(); ++i)
			{
				string select_feature;
				select_feature.clear();
				for (size_t j = 0; j < m_select_features[i].size(); ++j)
				{
					string feat_name = m_select_features[i][j];
					int feat_number = feature_collection.get_feature_number(feat_name);
					int value_index = feat_number_index[feat_number];
                    if (j == m_select_features[i].size()-1)
    					select_feature += feature_prefixes[value_index] + "@" + all_feature_values[value_index][row];
                    else
    					select_feature += feature_prefixes[value_index] + "@" + all_feature_values[value_index][row] + "+";
				}
				vecForCons.push_back(select_feature);
			}
			vecFeatAllCons.push_back(vecForCons);
		}

		vecAllFeatures.push_back(vecFeatAllCons);

		for (int nodeID = 0; nodeID < m_dataPreProc->m_intItemNum; nodeID++)
		{
			int predID = m_vecPredicate[predicate_index];
			if (!IsFilter(nodeID, predID))
			{
				//get position of unFiltered nodes, and push_back to vecPosVerb
				DepNode curNode;
				m_dataPreProc->m_myTree->GetNodeValue(curNode, nodeID);
				vecPosVerb.push_back(curNode.constituent);
			}
		}
		vecAllPos.push_back(vecPosVerb);
    }
}

//to construct a line of CoNLL2009 corpus format from ltpData.
//add by jiangfeng. 2010.1.31
void SRLBaselineExt::construct_lines(vector<string>& lines) const
{
	size_t row_count = m_dataPreProc->m_ltpData->vecWord.size();
	size_t predicate_count = m_vecPredicate.size();

	for (size_t id = 1; id <= row_count; ++id)
	{
		ostringstream line;
		line.str("");
		/*construct a line with element: word, pos, relation, .etc*/
		line << id << " "; // first column: id
		line << m_dataPreProc->m_ltpData->vecWord[id-1] << " "; // second column: form
		line << m_dataPreProc->m_ltpData->vecWord[id-1] << " "; // third column: lemma, same with form
		line << m_dataPreProc->m_ltpData->vecWord[id-1] << " "; // forth column: plemma, same with lemma
		line << m_dataPreProc->m_ltpData->vecPos[id-1] << " "; // fifth column: pos
		line << m_dataPreProc->m_ltpData->vecPos[id-1] << " "; // sixth column: ppos, same with ppos
		line << "_" << " "; // 7th column: feat: null
		line << "_" << " "; // 8th column: pfeat: null
		
        if (m_dataPreProc->m_ltpData->vecParent[id-1] == -2)
        {
            line << 0 << " ";
            line << 0 << " ";
        }
        else
        {
			line << m_dataPreProc->m_ltpData->vecParent[id-1] + 1 << " ";
			line << m_dataPreProc->m_ltpData->vecParent[id-1] + 1 << " ";
        }

		line << m_dataPreProc->m_ltpData->vecRelation[id-1] << " "; //deprel
		line << m_dataPreProc->m_ltpData->vecRelation[id-1] << " "; //pdeprel

		if (count(m_vecPredicate.begin(), m_vecPredicate.end(), id - 1) != 0) // fillpred
		{
			line << "Y" << " ";
            line << "Y" << " ";
		}
		else
        {
			line << "_" << " ";
            line << "_" << " ";
        }

		for (size_t args = 0; args < predicate_count - 1; ++args) // make room for args
			line << "_" << " ";
		line << "_";

		/*finish construct a line*/
		lines.push_back(line.str());
	}
}

//features need to be extracted are defined in the configure file "Chinese.xml"
//add by jiangfeng. 2010.1.31
void SRLBaselineExt::get_feature_config(
	FeatureCollection& feature_collection, 
	vector<int>& feature_numbers, 
	vector<string>& feature_prefixes, 
	const Configuration& configuration
) const {
	const vector<string> & noun_set = configuration.get_argu_config().get_noun_feature_names();
    const vector<string> & verb_set = configuration.get_argu_config().get_verb_feature_names();
	
	feature_numbers.clear();
    feature_prefixes.clear();
    for (size_t i=0; i<noun_set.size(); ++i)
    {
        const string& feature_name = noun_set[i];
        const int feature_number 
            = feature_collection.get_feature_number(feature_name);
        const string& feature_prefix
            = feature_collection.get_feature_prefix(feature_number);

        feature_numbers.push_back(feature_number);
        feature_prefixes.push_back(feature_prefix);
    }

    for (size_t i=0; i<verb_set.size(); ++i)
    {
        const string& feature_name = noun_set[i];
        const int feature_number 
            = feature_collection.get_feature_number(feature_name);
        const string& feature_prefix
            = feature_collection.get_feature_prefix(feature_number);

        if ( (find(feature_numbers.begin(), 
                   feature_numbers.end(),
                   feature_number)) == feature_numbers.end()) // not find
        {
            feature_numbers.push_back(feature_number);
            feature_prefixes.push_back(feature_prefix);
        }
    }
}

//features to be used is defined in the configure file "conll2009-arg.conf"
//add by jiangfeng. 2010.1.31
void SRLBaselineExt::open_select_config(
	const string& select_config,
	vector< vector<string> >& m_select_features
) const {
	ifstream conf_input(select_config.c_str());
	if (!conf_input)
	{
		throw runtime_error("select_config file cannot open!");
	}
	m_select_features.clear();
	string line;
	while (getline(conf_input, line))
	{
		if (line == "[VERB]")
		{
			continue;
		}
		else if ("" != line)
		{
			if ('#' == line[0])
			{
				continue;
			}
			vector<string> vec_str;
			replace(line.begin(), line.end(), '+', ' ');
			istringstream istr(line);
			string temp_str;
			while (istr >> temp_str)
			{
				vec_str.push_back(temp_str);
			}
			m_select_features.push_back(vec_str);
		}
	}
	conf_input.close();
}

//////////////////////////////////////////////////////////////////////////
bool SRLBaselineExt::IsFilter(int nodeID, int intCurPd) const
{
	DepNode depNode;
	m_dataPreProc->m_myTree->GetNodeValue(depNode, nodeID);

	//the punctuation nodes, current predicate node
	//changed for PTBtoDep, only filter the current predicate
	if( (nodeID == intCurPd) ||
		(depNode.parent < 0) ||
		( (depNode.constituent.first <= intCurPd) &&
		  (depNode.constituent.second >= intCurPd) ) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////
void SRLBaselineExt::ExtractConsFeatures(VecFeatForVerb& vecFeatAllCons) const
{
	int depNodeNum;
	int index;	

	depNodeNum = m_dataPreProc->m_intItemNum;
	index = 0;
	while (index < depNodeNum)
	{
		VecFeatForCons vecFeatCons;
		ConsFeaturesExt consFeat(m_dataPreProc, index);

		m_featMethod->ExtractConsFeat(vecFeatCons, &consFeat);
		vecFeatAllCons.push_back(vecFeatCons);

		for (VecFeatForCons::iterator itForFeat = vecFeatCons.begin(); itForFeat != vecFeatCons.end(); ++itForFeat)
		{
			cout << *itForFeat << " ";
		}
		cout << endl;

		index++;
	}
}

//////////////////////////////////////////////////////////////////////////
void SRLBaselineExt::ExtractPdFeatures(VecFeatForVerb& vecFeatAllPd) const
{
	vector<int>::const_iterator itPredicate;
	itPredicate = m_vecPredicate.begin();
	while (itPredicate != m_vecPredicate.end())
	{
		VecFeatForCons vecFeatPd;
		PdFeaturesExt pdFeat(m_dataPreProc, *itPredicate);

		m_featMethod->ExtrcatPdFeat(vecFeatPd, &pdFeat);
		vecFeatAllPd.push_back(vecFeatPd);
		itPredicate++;
	}
}
