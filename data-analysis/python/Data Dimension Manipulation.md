1. Apply function to each row/column 
```py
# method 1
df['new column perhaps'] = df.apply(lambda rec: rec.x - rec.y, axis = 1) # along column axis, ie. apply for each row
# method 2
def func(rec):
    return rec.x*rec.x
df['new column'] = df.apply(func, axis = 0)
# method 3
df['new column'] = df.x - df.y
# ----------------------------------------------------------------------- #
def func2(rec):
    return [rec.x*rec.x, rec.y*rec.y]   # multiple columns
df[['x_sq', 'y_sq']] = df.apply(func2, result_type = 'expand') # returns two series if result_type is expand. Without it, the apply function cannot return multiple columns
df.apply(func2, result_type = 'broadcast') # broadcast result along axis 0 (for each column). Only works if the dimensions fit 
```

2. Generalise a function to operate on Series or Dataframe
```py
def f(x, y):
    return x*y
vec_f = np.vectorize(f)
df.new = vec_f(df.x, df.y, otypes=[float])  # df.x and df.y are Series but f still works; datatype is the first input's type unless specify otype
```

3. iloc, loc, ix
```py
df.iloc[row_selections, column_selections]  # purely integer based, ie. from 0 to length of row or column respectively
df.loc[row_selections, column_selections] # label-based, ie. row or column names; OR conditions
df.ix[row_selections, column_selections] # DEPRECATED ALREADY. Combination of iloc and loc
# Examples
df.iloc[:, 2:4] # select columns 2 and 3
df.iloc[2:4, :] # select rows 2 and 3
df.loc['a':'c', ['x', 'y']] # select rows a to c, get columns x and y
df.loc[['a']] # additional [] to forcefully return DATAFRAME, else SERIES
df.loc[data['company_name'].apply(lambda x: len(x.split(' ')) == 4)] # conditions: has 4 words
```
- iloc and loc **do not create copies**, they execute in-place
> Chained Assignment
> - iloc and loc do not create copies. To create copies, use `df_copy = df.copy()`
> - Difference between `df['one']['second']` and `df.loc[:, ('one', 'second')]`
>   - `df['one']['second'] = value` is `df.__getitem__('one').__setitem__('second', value)`. It may be setting the value on a copy of `df['one']` or on the original `df`
>   - `df.loc[:, ('one', 'second')]` is `dfmi.loc.__setitem__((slice(None), ('one', 'second')), value)`. This guarantees changing the original `df`
  
4. concat, join, merge
```py
result = pd.concat([df1, df4], axis=1).reindex(df1.index)   # join according to index by default. merge side by side
result = df1.append(df4, sort=False)    # append is equivalent to concat in axis = 0. When DataFrames have different indices (possibly out of order), do not sort and leave them as they are
result = pd.concat([df1, df4], ignore_index=True, sort=False)   # do not merge due to index. Do not sort
result = df1.merge(df2, left_on='lkey', right_on='rkey', suffixes=('_left', '_right'))
result = df.set_index('key').join(other.set_index('key'), how = 'left') # how could also be right, inner, outer
result = df.join(other.set_index('key'), on='key')   # same as above, but df does not need to reindex because `on` species the column name of df to join on
```

5. Conditions
```py
df[(df['col'].between(1, 10)) & (df['col2'] == 2010)]
```

# Selection
## 1. Find k-th largest/smallest
```py
df.nlargest(3, ['population', 'area']) == df.sort_values(['population', 'area'], ascending=False).head(3)
# but more performant
```

# Filtering
## 1. `x IN ()`
```py
df = customers[~customers['id'].isin(orders['customerId'])]
```

# Manipulation
## 1. `IF(cond, then, else)`
```py
np.where((~employees['name'].str.startswith('M')) & (employees['employee_id'] % 2 == 1), employees['salary'], 0)
```