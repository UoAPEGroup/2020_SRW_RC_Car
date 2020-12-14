clear;
clc;

opts = detectImportOptions('ParametricSetup2_Result.xlsx');
opts.Sheet = 'ParametricSetup2_Result';
opts.SelectedVariableNames = [2:8];
opts.DataRange = '2:217';
M = readtable('ParametricSetup2_Result.xlsx', opts);

