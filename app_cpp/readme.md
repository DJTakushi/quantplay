
# todo

## convert
- [ ] algo.py
  - [x] algo
    - [x] AlgoData struct ("snapshot")
      - algo will handle its own internal data
    - [x] addData
    - [x] loadData [no, manager will load data.  algo has 1 responsibility]
    - [x] process (verdict)
- [ ] algomanager.py
  - [ ] init
  - [ ] getData
  - [ ] simulate
  - [ ] analyze
- [ ] apigetter.py
- [ ] csvconverter.py
- [ ] databaseconnector.py
- [ ] datagetter.py
- [x] daydata.py
- [x] dayrecorder.py
- [x] portfolio.py
- [x] transaction.py

## create algoController
- handles algo data & updates for algoManager
- algoController(*dbConnection)
  - (-) dbConnection
  - (-) algo
  - (-) latest_data_update_ts (timestamp for latest update of data; used for searching data)
  - (-) dataRetriever
    - list<*algoData> get_data() (gets data from database)
      - algoData is a derived struct unique to each algo
      - list<*algoData> get_dataSingle() (gets ONE data from database)
   - (+) updateData() gets list from dataRetriever and updates data in algo
    - (+) updateDataSingle() gets ONE from dataRetriever
  - (+) getTransaction()

## docekrize
- set up database
- populate database
- real control

## doxygen demo

## restructure
- [x] common (transactions, daydata)
- [x] algoX
- algoManager
  - algoManager
  - portfolio