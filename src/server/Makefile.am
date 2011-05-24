INCLUDES = -I. 

bin_PROGRAMS = ltp_server

ltp_server_SOURCES = ltp_server.cpp mongoose.c mongoose.h ltp_all_modules.conf

ltp_server_LDADD = \
  -L../_split_sentence -lsplitsnt \
  -L../_crfwordsegment -lcrfwordseg \
  -L../_crfwordsegment/crf++ -lcrfpp \
  -L../_crfwordsegment/util -lcrfutil \
  -L../_svmtagger -lpostagger \
  -L../_gparser -lgparser \
  -L../_ner -lner \
  -L../_wsd -lwsd \
  -L../_srl -lsrl \
  -L../__xml4nlp -lxml4nlp \
  -L../__maxent -lme \
  -L../__ltp_dll -lltp \
  -L../__util -lutil 

ltp_server_LDFLAGS = \
  -ldl -lpthread -lboost_regex
