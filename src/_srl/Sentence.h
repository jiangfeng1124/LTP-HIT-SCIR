#ifndef _SENTENCE_H_
#define _SENTENCE_H_

#include <string>
#include <vector>
#include "Configuration.h"
#include "tree.hh"
#include <boost/multi_array.hpp>

#include <iostream>

typedef size_t RowID;
typedef tree<RowID> SRLTree;

class Predicate
{
    // predicate type: verb, noun, unknown
    //  PRED_UNKNOWN is returned by get_predicate_type* calls to indicate 
    //  that the concerned word is not a predicate
public:
    enum PRED_TYPE {PRED_VERB, PRED_NOUN, PRED_UNKNOWN};
    
    explicit Predicate(size_t _row, int _type=PRED_UNKNOWN)
        : row(_row), type(_type) {}

    size_t row;
    int    type;
};

class Sentence
{
public:
    Sentence()
    {
    }

    // a Sentence can be create from:
    void from_corpus_block(
        const std::vector<std::string> &corpus_block,
        const Configuration& config);

    // a Sentence can be transformed to:
    const std::string to_corpus_block() const;

    // set predicate
//    void set_predicates(const std::vector<size_t> &predicate_rows);

    // set predicate (affects only FIELD_PRED, for predicate sense setting)
    void set_PRED(const size_t row, const std::string &PRED);

    // clear the sentence
    void clear();
private:
    Sentence(const Sentence &);
    Sentence& operator=(const Sentence &);

public:
    enum FIELD
    {
        FIELD_FORM, FIELD_LEMMA, FIELD_PLEMMA, FIELD_POS, FIELD_PPOS, 
        FIELD_FEAT, FIELD_PFEAT, FIELD_HEAD, FIELD_PHEAD, FIELD_DEPREL, 
        FIELD_PDEPREL, FIELD_FILLPRED, FIELD_PRED, FIELD_NUMBER
    }; // see CoNLL2009 shared task web site for field definitions
public:
    // get row count
    const size_t get_row_count() const
    {
        return m_row_count;
    }

    // get the parse tree node corresponding to a specified row
    const SRLTree::iterator& get_node_of_row(const size_t row) const
    {
        return m_node_of_row[row];
    }

    // corpus field getter:
    const std::string& get_field(const size_t row, const int field) const
    {
        return m_fields[row][field];
    }

    const std::string& get_FORM(const size_t row) const
    {
        return get_field(row, FIELD_FORM);
    }

    const std::string& get_PLEMMA(const size_t row) const
    {
        return get_field(row, FIELD_PLEMMA);
    }

    const std::string& get_PPOS(const size_t row) const
    {
        return get_field(row, FIELD_PPOS);
    }

    const std::string& get_PFEAT(const size_t row) const
    {
        return get_field(row, FIELD_PFEAT);
    }

    const std::string& get_PHEAD_str(const size_t row) const
    {
        return get_field(row, FIELD_HEAD);
    }

    const size_t get_PHEAD(const size_t row) const
    {
        return m_HEADs[row];
    }

    const std::string& get_PDEPREL(const size_t row) const
    {
        return get_field(row, FIELD_DEPREL);
    }

    const std::string& get_FILLPRED(const size_t row) const
    {
        return get_field(row, FIELD_FILLPRED);
    }

    const std::string& get_PRED(const size_t row) const
    {
        return get_field(row, FIELD_PRED);
    }

    // get and set semantic arguments
    const std::string& get_argument(
        const size_t predicate_index,
        const size_t row) const;

    void set_argument(
        const size_t predicate_index,
        const size_t row,
        const std::string& argument_name);

    // get predicates
    const std::vector<Predicate>& get_predicates() const
    {
//        std::cout<<"get_predicates (const version)"<<std::endl;
        return m_predicates;
    }

    // get predicates (reference)
    std::vector<Predicate>& get_predicates()
    {
        return m_predicates;
    }

    // get parse tree
    const SRLTree& get_parse_tree() const
    {
        return m_parse_tree;
    }

private:
    // make storage space for a specified number of rows
    void resize_(const size_t row_count);
    // decide predicate type according to the POS of the row
    Predicate::PRED_TYPE get_predicate_type_(
    const Configuration &config,
    const size_t row);
    // same as above, but never returns PRED_TYPE_UNKNOWN
    Predicate::PRED_TYPE get_predicate_type_try_hard_(
    const Configuration& config,
    const size_t row);

private:
    size_t                                 m_row_count;
    boost::multi_array<std::string, 2>     m_fields;
    std::vector<Predicate>                 m_predicates;
    std::vector<std::vector<std::string> > m_argument_columns;
    std::vector<size_t>                    m_HEADs;
    SRLTree                                m_parse_tree;
    std::vector<SRLTree::iterator>         m_node_of_row;
};

#endif
